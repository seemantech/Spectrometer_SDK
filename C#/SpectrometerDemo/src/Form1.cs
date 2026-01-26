using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;//Stopwatch
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;
using System.Threading;
using System.IO;
using System.IO.Ports;
using System.Net.Sockets;
using System.Net;

namespace SpectrometerCSharpDemo
{
    struct Spectrometer
    {
        public UInt32 nIntUS;//积分时间 微秒
        public UInt16 nAverage;
        public UInt16 nBoxcar; 
        public int nNumPixels; // the pixels number of spectrometer
        public string strSN; // S/N of spectrometer
        public float[] fWavelength;//Wavelength Array of Spectrometer (Read Only Once when Device is online)
        public float[] fIntensity; //Intensity  Array of Spectrometer
        public List<Byte> buf; //buffer for spectrometer data return
        public int cntScans;
        public int cntTrigs;
        public DateTime timeStamp;

        public int MAX_FRAMES;
        public List<UInt16[]> frames; //buf direct to frames
        public List<DateTime> sampleTimes;
        public void bufToIntensity()
        {
            int nOffset;

            timeStamp = DateTime.Now;

            UInt16 wIntensity;
            UInt16[] pNewData = new UInt16[nNumPixels];
            for (int i = 0; i < nNumPixels; i++)
            {
                nOffset = 6 + 2 * i;
                wIntensity = (UInt16)(buf[nOffset] * 256 + buf[nOffset + 1]);
                fIntensity[i] = (float)wIntensity;
                pNewData[i] = wIntensity;
            }
            frames.Add(pNewData);
            sampleTimes.Add(timeStamp);

            //数量太多，删除
            if (frames.Count > MAX_FRAMES) frames.RemoveAt(0);
            if (sampleTimes.Count > MAX_FRAMES) sampleTimes.RemoveAt(0);
            //cntScans = frames.Count;
            cntScans++;
        }
    };


    public partial class Form1 : Form
    {
        SMT.OEM.Logger logger = new SMT.OEM.Logger();
        SMT.OEM.DataProcess dataProcess = new SMT.OEM.DataProcess();

        List<UInt16> listCMD = new List<UInt16>();

        int m_iRunning = 0;
        bool m_bTrigMode = false;
        bool m_bVCP_Frist = true;
        float m_dIndicateX = 500;
        System.Windows.Forms.Timer graphTimer = null;
        System.Windows.Forms.Timer saveTimer = null;

        Spectrometer m_sp;

        Byte[] pBufIN = new Byte[4096 * 8];
        Byte[] pBufIN_LAN = new Byte[4096 * 4 + 8 + 128];

        //FPS Calc
        int nTickFPS_Beg = System.Environment.TickCount;
        int cntFPS_Beg = 0;

        float m_fFPS = 0;
        int nLoopsFPS = 0;

        SpectrometerTCPClient tcp = new SpectrometerTCPClient();

        //LAN/WIFI Socket 
        Socket socket;
        NetworkStream tcpStream;
        bool m_bOpenLAN = false;


        ////////////////////////////////////////////////////////////////////////
        // Initialization
        ////////////////////////////////////////////////////////////////////////

        public Form1()
        {
            InitializeComponent();

            m_sp.MAX_FRAMES = 20000;
            m_sp.nIntUS = 10000;//10ms
            m_sp.nAverage = 1;
            m_sp.nBoxcar = 1;
            m_sp.nNumPixels = 2048;
            m_sp.fWavelength = new float[m_sp.nNumPixels];
            m_sp.fIntensity = new float[m_sp.nNumPixels];
            m_sp.buf = new List<byte>();
            m_sp.frames = new List<UInt16[]>();
            m_sp.sampleTimes = new List<DateTime>();
            // initialize logger
            logger.setTextBox(textBoxEventLog);

            // tooltips
            //toolTip1.SetToolTip(checkBoxEnableDataCollection, "Save acquisitions to a CSV file");
            toolTip1.SetToolTip(IntegrationTimeMS, "Set Integration Time of Spectrometer in Milliseconds");
            toolTip1.SetToolTip(checkBoxEnableDataCollection, "Continuous Scan Mode");
            toolTip1.SetToolTip(btnScan, "Single Scan");
            toolTip1.SetToolTip(btnUnzoom, "Unzoom Graph Coordinates");
            toolTip1.SetToolTip(btnSave, "Save Newest Spectrum Data to Text File");
            toolTip1.SetToolTip(textBox1, String.Format("Keep the most recent {0} Frames in RAM!", m_sp.MAX_FRAMES));
            toolTip1.SetToolTip(btnSaveBuffer, "Save Spectrum Datas buffered in RAM ");
            toolTip1.SetToolTip(btnConnectVCP, "Connect Spectrometer through USB/VCP/SERIAL PORT");
            toolTip1.SetToolTip(btnConnectLAN, "Connect Spectrometer through LAN/WIFI");

            // timer to drive the graph (often at a lower rate than acquisitions)
            graphTimer = new System.Windows.Forms.Timer();
            graphTimer.Interval = 50;// refresh chart graph at 20Hz
            graphTimer.Tick += graphTimer_Tick;
            m_iRunning = 0x7FFFFFFF;

            saveTimer = new System.Windows.Forms.Timer();
            saveTimer.Interval = 1000; // save 1Hz
            saveTimer.Tick += saveTimer_Tick;

            InitDataGridView();
            InitGraph();

            //string[] PortNames = SerialPort.GetPortNames();    //获取本机串口名称，存入PortNames数组中
            //for (int i = 0; i < PortNames.Count(); i++)
            //{
            //    cbxSerilPort.Items.Add(PortNames[i]);   //将数组内容加载到comboBox控件中
            //}

            //禁用跨线程调用检查
            //CheckForIllegalCrossThreadCalls = false;
        }

        /*
        private void ConnectLAN()
        {
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                m_bOpenLAN = true;
                socket.Connect(new IPEndPoint(IPAddress.Parse("127.0.0.1"), 6666));//public void Connect(IPAddress[] addresses, int port);
            }
            catch (Exception e)
            {
                MessageBox.Show(String.Format("Connect Error"));
                m_bOpenLAN = false;
                return;
            }

            tcpStream = new NetworkStream(socket);//创建收发数据流
            tcpStream.BeginRead(pBufIN_LAN, 0, pBufIN_LAN.Length, LAN_ReceiveEnd, socket);

            //bool bConnect = LAN_SendData(new Byte[1]);
            //MessageBox.Show(String.Format("{0}", bConnect));

            //socket.Connected
            //byte[] data = Encoding.UTF8.GetBytes("hello i'm client");
            //int len = data.Length;
            //byte[] data_len = new byte[4];
            //data_len[0] = (byte)((len >> 8 * 3) & 0xFF);
            //data_len[1] = (byte)((len >> 8 * 2) & 0xFF);
            //data_len[2] = (byte)((len >> 8 * 1) & 0xFF);
            //data_len[3] = (byte)(len & 0xFF);

            //byte[] data_all = new byte[len + 4];
            //Array.Copy(data_len, 0, data_all, 0, data_len.Length);
            //Array.Copy(data, 0, data_all, 4, data.Length);
            //byte[] buffer = new byte[1024];
            //int count = socket.Receive(buffer, SocketFlags.None);
            //if (count > 0)
            //{
            //    string msg = Encoding.UTF8.GetString(buffer, 0, count);

            //    this.Text = msg;
            //}
            //socket.BeginReceive()
        }

        private void LAN_ConnectAsync()
        {
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            IAsyncResult conAsync = socket.BeginConnect("192.168.31.177", 6666, null, socket);//开始连接
            //bool success = conAsync.AsyncWaitHandle.WaitOne(6000, true);//堵塞 直到收到反馈

            bool success = conAsync.AsyncWaitHandle.WaitOne(500, true);//堵塞 直到收到反馈
            if (success && socket.Connected)//成功连接
            {
                socket.EndConnect(conAsync);//关闭异步对象
                tcpStream = new NetworkStream(socket);//创建收发数据流
                socket.SetSocketOption(SocketOptionLevel.Tcp, SocketOptionName.NoDelay, true);//无延迟发送

                // LAN_Receive();//开始接收

                //tcpStream = new NetworkStream(socket);//创建收发数据流
                tcpStream.BeginRead(pBufIN_LAN, 0, pBufIN_LAN.Length, LAN_ReceiveEnd, socket);
                m_bOpenLAN = true;
            }
            else
            {

                m_bOpenLAN = false; //超时或者连接失败
            }
            MessageBox.Show(String.Format("{0}", m_bOpenLAN));
            //LAN_SendData(new Byte[0]);
        }

       
        private void LAN_SendData(byte[] data, int offset, int size)
        {
            if (!m_bOpenLAN) return;

            TCP_Write(data, offset, size);
            return;

            //bOpenLAN = false;
            //bool blockingState = socket.Blocking;
            try
            {
                //data_all = new byte[5] { 0x10, 0, 0, 0, 0 };
                //socket.Blocking = false;
                socket.Send(data);
                //tcpStream.Flush();

                //socket.Send(data,offset,size, 0);
                tcpStream.BeginRead(pBufIN_LAN, 0, pBufIN_LAN.Length, LAN_ReceiveEnd, socket);
                //tcpStream.BeginWrite(data, offset, size, EndSend, socket);
                //socket.BeginReceiveFrom

                m_bOpenLAN = true;
            }
            catch (SocketException e)
            {
                if (e.NativeErrorCode.Equals(10035))// 产生 10035 == WSAEWOULDBLOCK 错误，说明被阻止了，但是还是连接的 
                {
                    m_bOpenLAN = true;
                }

                MessageBox.Show(String.Format("Lan Send Error {0}", m_bOpenLAN));
            }
            finally
            {
            }
        }
        */

        private void LAN_ReceiveEnd(IAsyncResult asyncReceive)
        {
            try
            {
                int len = tcpStream.EndRead(asyncReceive);

                //long a = tcpStream.Length;
                if (len > 0)
                {
                    if (listCMD[0] == 0x3020)
                    {
                        MessageBox.Show("ReadWavelength() 3020");
                    }
                    //if (listCMD[0] == 0x4010)
                    //{
                    //    MessageBox.Show("ReadIntensity() 4010");
                    //}
                    Data_Dealer(pBufIN_LAN, len);

                    if (m_sp.buf.Count > 0)
                    {
                        m_sp.buf.Clear();
                        if (listCMD.Count <= 0)
                        {
                            listCMD.Add(0x4010);
                        }
                        EXE_listCMD();
                    }
                    return;
                }
                else
                {
                   
                }
            }
            catch (Exception e)
            {
            }

            if (m_sp.buf.Count > 0)
            {
                //LAN_SendData(new Byte[0],0,0);
                m_sp.buf.Clear();
                //EXE_listCMD();
            }
            if (listCMD.Count <= 0)
            {
                listCMD.Add(0x4010);
            }
            EXE_listCMD();
        }

        private void InitDataGridView()
        {
            dataGridView1.AutoSizeRowsMode = DataGridViewAutoSizeRowsMode.AllCells; //根据Header和所有单元格的内容自动调整行的高度
            dataGridView1.DefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;    //设置内容对齐方式和字体         
            //dataGridView_Report.Font = new Font("宋体", 10);

            dataGridView1.ReadOnly = true; //设置所有单元格都不可编辑
            dataGridView1.RowHeadersWidth = 15; //设置标题头列宽
            dataGridView1.AllowUserToAddRows = false;   //不可以增加空行

            //添加表头
            for (int i = 0; i < 2; i++)
            {
                dataGridView1.Columns.Add(new DataGridViewTextBoxColumn());
            }
            //指定标题列宽
            dataGridView1.Columns[0].Width = 85;
            dataGridView1.Columns[1].Width = 90;
            //添加标题字符
            dataGridView1.Columns[0].HeaderText = "Wavelength";
            dataGridView1.Columns[1].HeaderText = "Intensity";

        }

        private void InitGraph()
        {
            chartSpectrum.Series.Add(new Series());//chartSpectrum.Series.Add(graphSeries[0]);
            chartSpectrum.Series[0].ChartType = SeriesChartType.FastLine;// SeriesChartType.Line;
            chartSpectrum.Series[0].Name = String.Format("Spectrum");
            chartSpectrum.Series[0].Color = Color.Blue;
            chartSpectrum.Series[0].Points.Clear();
            for (int i = 0; i < m_sp.nNumPixels; i++)
            {
                chartSpectrum.Series[0].Points.AddXY(i, i);
            }

            chartSpectrum.Series.Add(new Series());
            chartSpectrum.Series[1].ChartType = SeriesChartType.FastLine;// SeriesChartType.Line;
            chartSpectrum.Series[1].Name = String.Format("Overflow");
            chartSpectrum.Series[1].Color = Color.Red;
            chartSpectrum.Series[1].Points.Clear();
            chartSpectrum.Series[1].Points.AddXY(-2000, 65535);
            chartSpectrum.Series[1].Points.AddXY(2000, 65535);

            chartSpectrum.Series.Add(new Series());
            int nIndex = 2;
            chartSpectrum.Series[nIndex].ChartType = SeriesChartType.FastLine;// SeriesChartType.Line;
            chartSpectrum.Series[nIndex].Name = String.Format("indicate");
            chartSpectrum.Series[nIndex].Color = Color.Purple;
            chartSpectrum.Series[nIndex].Points.Clear();
            m_dIndicateX = 500;
            chartSpectrum.Series[nIndex].Points.AddXY(m_dIndicateX, -1000000);
            chartSpectrum.Series[nIndex].Points.AddXY(m_dIndicateX, 1000000);
            SetIndicate(m_dIndicateX);

            //Coordinate X
            chartSpectrum.ChartAreas[0].AxisX.ScrollBar.IsPositionedInside = false;
            chartSpectrum.ChartAreas[0].AxisX.LabelStyle.Format = "F0";
            chartSpectrum.ChartAreas[0].AxisX.Minimum = 150D;
            chartSpectrum.ChartAreas[0].AxisX.Maximum = 1150D;
            //chartSpectrum.ChartAreas[0].AxisX.ScaleView.Zoomable = false;
            //chartSpectrum.ChartAreas[0].AxisX.MajorGrid.Interval = 100;

            //Coordinate Y
            chartSpectrum.ChartAreas[0].AxisY.ScrollBar.IsPositionedInside = false;
            chartSpectrum.ChartAreas[0].AxisY.LabelStyle.Format = "F0";
            chartSpectrum.ChartAreas[0].AxisY.Minimum = -1000D;//0D;//
            chartSpectrum.ChartAreas[0].AxisY.Maximum = 70000D;
            chartSpectrum.ChartAreas[0].AxisY.TextOrientation = TextOrientation.Stacked;//TextOrientation.Horizontal;
            //chartSpectrum.ChartAreas[0].AxisY.ScaleView.Zoomable = false;
            //chartSpectrum.ChartAreas[0].AxisY.LabelStyle.Format = "F0";

            chartSpectrum.ChartAreas[0].CursorX.Interval = 1D;
            chartSpectrum.ChartAreas[0].CursorX.IsUserSelectionEnabled = true;
            //chartSpectrum.ChartAreas[0].CursorX.LineDashStyle = ChartDashStyle.Dot;
            chartSpectrum.ChartAreas[0].CursorY.Interval = 1D;
            chartSpectrum.ChartAreas[0].CursorY.IsUserSelectionEnabled = true;

            //LineAnnotation  myLine = new LineAnnotation();
            //myLine.Name = "myLine";
            //myLine.X = 500;
            //myLine.Y = 500;
            //myLine.AnchorX = 500;
            //myLine.AnchorY = 500;
            //myLine.AxisX.
            //chartSpectrum.Annotations.Add(myLine);

            //chartSpectrum.BorderlineDashStyle = ChartDashStyle.Dot;
            Refresh();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            btnScan.Enabled = false;
            ConnectSpectrometersVCP();

            if (serialPort1.IsOpen)
            {
                //textBoxIP.Visible = false;
                //btnConnectLAN.Visible = false;
            }
            else
            {
                ConnectSpectrometersLAN();
            }
            graphTimer.Start();
            //Stopwatch sw = new Stopwatch();
            //sw.Start();
            //sw.ElapsedMilliseconds;//sw.ElapsedMilliseconds.ToString("0000");
            //sw.Stop();
            //GetSerialNO();
            //ReadWavelength();
            //ReadIntensity(m_sp.nIntUS, m_sp.nAverage, m_sp.nBoxcar);
        }


        private void SendData(Byte[] cmd, int offset, int size)
        {
            if (m_bVCP_Frist)
            {
                if (serialPort1.IsOpen) { serialPort1.Write(cmd, offset, size); return; }
                if (m_bOpenLAN) { TCP_Write(cmd, offset, size); return; } //LAN_SendData(cmd, offset, size);
            }
            else
            {
                if (m_bOpenLAN) { TCP_Write(cmd, offset, size); return; } //LAN_SendData(cmd, offset, size);
                if (serialPort1.IsOpen) { serialPort1.Write(cmd, offset, size); return; }
            }
        }
        private void EXE_listCMD()
        {
            //此函数为多线程执行,不能有GUI相关控件的操作,可以用MessageBox
            if (!serialPort1.IsOpen && !m_bOpenLAN)
            {
                //MessageBox.Show(String.Format("Serial Port Closed"));
                return;
            }
            if (listCMD.Count < 1)
            {
                //MessageBox.Show(String.Format("list count < 1"));
                //if (bOpenLAN) LAN_SendData(new Byte[0], 0, 0); //Read Data IN Trigger Mode
                return;
            }

            if (listCMD[0] == 0x4010)//ReadIntensity  读取光谱仪的强度数组数据
            {
                Byte[] cmd = new Byte[16] { 0xAA, 0x66, 0x40, 0x10, 0x00, 0x08, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x01, 0x00, 0x01, 0xFF, 0xFF };
                cmd[6] = (Byte)(m_sp.nIntUS >> 24);
                cmd[7] = (Byte)(m_sp.nIntUS >> 16);
                cmd[8] = (Byte)(m_sp.nIntUS >> 8);
                cmd[9] = (Byte)(m_sp.nIntUS);
                cmd[10] = (Byte)(m_sp.nAverage >> 8);
                cmd[11] = (Byte)(m_sp.nAverage);
                cmd[12] = (Byte)(m_sp.nBoxcar >> 8);
                cmd[13] = (Byte)(m_sp.nBoxcar);
                SendData(cmd, 0, 16); 
                return;
            }

            if (listCMD[0] == 0x3010)//GetNumPixels 获取光谱仪像素个数，像素个数决定了Wavelength[]和Intensity[]的数组长度。
            {
                Byte[] cmd = new Byte[8] { 0xAA, 0x66, 0x30, 0x10, 0x00, 0x00, 0xFF, 0xFF };
                SendData(cmd, 0, 8);
                return;
            }
            if (listCMD[0] == 0x1002)//GetSerialNO 获取光谱仪序列号
            {
                Byte[] cmd = new Byte[8] { 0xAA, 0x66, 0x10, 0x02, 0x00, 0x00, 0xFF, 0xFF };
                SendData(cmd, 0, 8);
                return;
            }
            if (listCMD[0] == 0x3020)//GetWavelength  获取光谱仪的波长分布数组，仅需调用一次。 波长数组在光谱仪出厂后不会发生改变。
            {
                Byte[] cmd = new Byte[8] { 0xAA, 0x66, 0x30, 0x20, 0x00, 0x00, 0xFF, 0xFF };
                SendData(cmd, 0, 8);
                return;
            }

            if (listCMD[0] == 0x4051) //Enter Trigger Mode 进入触发采集模式
            {
                Byte[] cmd = new Byte[12] { 0xAA, 0x66, 0x40, 0x51, 0x00, 0x04, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF };
                cmd[6] = (Byte)(m_sp.nIntUS >> 24);
                cmd[7] = (Byte)(m_sp.nIntUS >> 16);
                cmd[8] = (Byte)(m_sp.nIntUS >> 8);
                cmd[9] = (Byte)(m_sp.nIntUS);
                SendData(cmd, 0, 12); 
                return;
            }

            if (listCMD[0] == 0x4052) //Exit Trigger Mode 退出触发采集模式
            {
                Byte[] cmd = new Byte[8] { 0xAA, 0x66, 0x40, 0x52, 0x00, 0x00, 0xFF, 0xFF };
                SendData(cmd, 0, 8); 
                return;
            }
        }


        private void ConnectSpectrometersVCP()
        {
            if (serialPort1.IsOpen) return;

            string[] PortNames = SerialPort.GetPortNames();    //获取本机串口名称，存入PortNames数组中
            //if (PortNames.Count() < 1) return;
            if (PortNames.Length < 1) return;

            //for 
            {
                serialPort1.BaudRate = 115200;
                serialPort1.PortName = PortNames[PortNames.Length - 1];//连接最后一个串口 //PortNames[0];//连接第一个串口 "COM6"; //"COM59";
                //serialPort1.DiscardInBuffer();//清空上次可能遗留的数据
                //serialPort1.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);//串口接收数据函数,消息驱动
                try
                {
                    serialPort1.Open();
                }
                catch (Exception e)
                {
                    serialPort1.Close();
                    setStatusVCP();
                    return;
                }

                if (serialPort1.IsOpen)
                {
                    serialPort1.DiscardInBuffer();//清空上次可能遗留的数据
                    serialPort1.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);

                    listCMD.Clear();//串口重复连接的情况
                    listCMD.Add(0x3010);
                    listCMD.Add(0x1002);
                    listCMD.Add(0x3020);
                    listCMD.Add(0x4010);
                    EXE_listCMD();
                }
                setStatusVCP();
            }
        }

        private void setStatusVCP()
        {
            if (serialPort1.IsOpen)
            {
                labelStatusVCP.Text = "Connected: " + serialPort1.PortName;
                labelStatusVCP.ForeColor = Color.Blue;
                btnConnectVCP.Enabled = false;
            }
            else
            {
                labelStatusVCP.Text = "unconnected";
                labelStatusVCP.ForeColor = Color.Red;
                btnConnectVCP.Enabled = true;
            }
        }

        private void ConnectSpectrometersLAN()
        {
            //if (m_bOpenLAN) return;

            TCP_Close();
            TCP_Connect(textBoxIP.Text, 6666, 500);//TCP_Connect("192.168.31.177", 6666);

            if (m_bOpenLAN)
            {
                m_sp.buf.Clear();
                listCMD.Clear();//串口重复连接的情况
                listCMD.Add(0x3010);//GetNumPixels
                listCMD.Add(0x1002);//GetSerialNO
                listCMD.Add(0x3020);//ReadWavelength()
                listCMD.Add(0x4010);//ReadIntensity()
                //Thread.Sleep(200);
                EXE_listCMD();
            }
            UpdateStatusLAN();
        }
        private void UpdateStatusLAN()
        {
            if (m_bOpenLAN)
            {
                textBoxIP.ForeColor = Color.Blue;
                btnConnectLAN.Enabled = false;
            }
            else
            {
                textBoxIP.ForeColor = Color.Red;
                btnConnectLAN.Enabled = true;
            }
        }

        private void Data_Dealer(Byte[] bufIN, int cbRead)
        {
            //添加新数据到list
            for (int i = 0; i < cbRead; i++)
            {
                m_sp.buf.Add(bufIN[i]);
            }

            //检查起始地址0xAA
            while (m_sp.buf.Count > 1)
            {
                if (m_sp.buf[0] != 0xAA)
                {
                    m_sp.buf.RemoveAt(0);
                }
                else
                {
                    break;
                }
            }
            if (m_sp.buf.Count < 6) return;//收到6个字节就可以确定数据包的大小,

            int cbTotal = m_sp.buf[4] * 256 + m_sp.buf[5] + 8;//payload 大小在[4][5]字节内

            if (m_sp.buf.Count < cbTotal) return;//数据包还未完整接收

            int nCMDType = m_sp.buf[2] * 256 + m_sp.buf[3];

            //MessageBox.Show(String.Format("CMD:0x{0:X}", nCMDType));

            if (nCMDType == 0x4010) //ReadIntensity();
            {
                m_sp.bufToIntensity();
                //m_sp.cntScans++;

                listCMD.RemoveAt(0);//listCMD.Remove(0x4010);//

                m_iRunning--;
                if (m_iRunning > 0)//&& listCMD.Count == 0)//如果命令列表为NULL，那么添加新命令
                {
                    listCMD.Add(0x4010);//继续ReadIntensity()
                }
                m_sp.buf.RemoveRange(0, cbTotal);
                EXE_listCMD();
                return;
                //MessageBox.Show("ReadIntensity");
            }

            //if (m_sp.buf[1] != 0x66) //ErrorCode: can't match Command Code
            //{
            //    listCMD.RemoveAt(0);
            //    m_sp.buf.RemoveRange(0, cbTotal);
            //    EXE_listCMD();
            //    //MessageBox.Show("ReadIntensity");
            //    return;

            //}


            if (nCMDType == 0x4051) //Enter Trig Mode() + receive trigger data
            {
                if (cbTotal == m_sp.nNumPixels * 2 + 8) //receive trig data
                {
                    m_sp.bufToIntensity();
                    m_sp.cntTrigs++;
                }
                else if (cbTotal == 8) //Enter Trig Mode()
                {
                    m_bTrigMode = true;
                    listCMD.Clear();//在这里可以Clear(),在GUI部分不可Clear();//listCMD.RemoveAt(0);//listCMD.Remove(0x4051);//后面必定有ReadIntensity，必须Clear
                    //MessageBox.Show("Enter Trig Mode");
                }
                m_sp.buf.RemoveRange(0, cbTotal);
                EXE_listCMD();
                return;
            }

            if (nCMDType == 0x4052) //Exit Trig Mode()
            {
                m_bTrigMode = false;
                listCMD.Clear();
                listCMD.Add(0x4010);//switch to normal mode : ReadIntensity
               //MessageBox.Show("Exit Trig Mode");
                m_sp.buf.RemoveRange(0, cbTotal);
                EXE_listCMD();
                return;
            }

            if (nCMDType == 0x3010) //GetNumPixels();
            {
                m_sp.nNumPixels = (UInt16)(m_sp.buf[6] * 256 + m_sp.buf[7]);
                m_sp.fWavelength = new float[m_sp.nNumPixels];
                m_sp.fIntensity = new float[m_sp.nNumPixels];
                //MessageBox.Show(String.Format("Pixels:{0}", m_sp.nNumPixels));
                listCMD.RemoveAt(0);//命令已完成，删除
                //MessageBox.Show("GetNumPixels");
                for (int i = 0; i < m_sp.fWavelength.Length; i++)
                {
                    m_sp.fWavelength[i] = i;
                }
                m_sp.buf.RemoveRange(0, cbTotal);
                EXE_listCMD();
                return;
            }

            if (nCMDType == 0x1002) //GetSerianNo();
            {
                m_sp.strSN = System.Text.Encoding.UTF8.GetString(m_sp.buf.ToArray(), 6, 32);
                listCMD.RemoveAt(0);//listCMD.Remove(0x1020);//
                //MessageBox.Show("GetSerianNo");
                m_sp.buf.RemoveRange(0, cbTotal);
                EXE_listCMD();
                return;
            }

            if (nCMDType == 0x3020) //ReadWavelength();
            {
                Byte[] data = new Byte[4];
                for (int i = 0; i < m_sp.nNumPixels; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        data[j] = m_sp.buf[6 + 4 * i + j];
                    }
                    m_sp.fWavelength[i] = System.BitConverter.ToSingle(data, 0);
                }
                listCMD.RemoveAt(0);//listCMD.Remove(0x3020); //
                //MessageBox.Show("ReadWavelength");
                m_sp.buf.RemoveRange(0, cbTotal);
                EXE_listCMD();
                return;
            }

           
        }

        //光谱仪数据接收处理部分，非常重要
        //Async 异步接收数据部分
        private void port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try 
            {
                int cbRead = serialPort1.Read(pBufIN, 0, 4096 * 4 + 8);
                Data_Dealer(pBufIN, cbRead);//处理不同的光谱仪命令返回的数据
            }
            catch
            {
                //MessageBox.Show(String.Format("Port Error!"));
            }
        }


        private void updateSpectrometersFromGUI()
        {
            m_sp.nIntUS = Convert.ToUInt32(IntegrationTimeMS.Value * 1000);
            m_sp.nAverage = Convert.ToUInt16(ScansAverage.Value);
            m_sp.nBoxcar = Convert.ToUInt16(ScansBoxcar.Value);
        }

        ////////////////////////////////////////////////////////////////////////
        // Graphing
        ////////////////////////////////////////////////////////////////////////

        private void updateGraph()
        {
            try
            {
                // foreach (int specIndex in specIndices)
                if (m_sp.nNumPixels > 10)
                {
                    chartSpectrum.Series[0].Points.Clear();
                    for (int i = 0; i < m_sp.nNumPixels; i++)
                    {
                        //UInt16 wIntensity = (UInt16)(pBufIN[2 * i] + pBufIN[2 * i + 1] * 256);
                        chartSpectrum.Series[0].Points.AddXY(m_sp.fWavelength[i], m_sp.fIntensity[i]);
                    }
                }
                chartSpectrum.Refresh();
            }
            catch (Exception e)
            {
                logger.display("ERROR: caught exception during graphing: {0}", e);
            }
            //Refresh();
        }

        private void updateDataGridView()
        {
            try
            {
                //如果Rows < Pixels
                int nOrgCount = dataGridView1.Rows.Count;
                if (nOrgCount < m_sp.nNumPixels)
                {
                    dataGridView1.Rows.Add(m_sp.nNumPixels - nOrgCount);
                }

                //如果 Rows > Pixels
                while (dataGridView1.Rows.Count > m_sp.nNumPixels)
                {
                    dataGridView1.Rows.RemoveAt(dataGridView1.Rows.Count - 1);
                }

                for (int i = 0; i < m_sp.nNumPixels; i++)
                {

                    dataGridView1.Rows[i].Cells[0].Value = m_sp.fWavelength[i];
                    dataGridView1.Rows[i].Cells[1].Value = m_sp.fIntensity[i];
                }
                //dataGridView1.Refresh();// Refresh();

            }
            catch (Exception e)
            {
                logger.display("ERROR: caught exception during graphing: {0}", e);
            }
            //Refresh();

        }

        ////////////////////////////////////////////////////////////////////////
        // GUI Events
        ////////////////////////////////////////////////////////////////////////

        private void btnScan_Click(object sender, EventArgs e)
        {
            updateSpectrometersFromGUI();
            m_iRunning = 1;//0x7FFFFFFF
            //ReadIntensityAsync(m_sp.nIntUS, m_sp.nAverage, m_sp.nBoxcar);
            listCMD.Add(0x4010);
            EXE_listCMD();
        }


        private void graphTimer_Tick(object sender, EventArgs e)
        {
            //if (m_bRunning > 0)
            {

                label10.Text = String.Format("{0} cmd,busize = {1}", listCMD.Count, m_sp.buf.Count);
                updateSpectrometersFromGUI();
                {
                    nLoopsFPS++;
                    if (nLoopsFPS % 15 == 0)// 10 * 100ms 计算时间
                    {
                        int nTickFPS_End = System.Environment.TickCount;

                        int nSpan = nTickFPS_End - nTickFPS_Beg;
                        int nScans = m_sp.cntScans - cntFPS_Beg;
                        m_fFPS = nScans * 1000f / nSpan;
                        nTickFPS_Beg = nTickFPS_End;
                        cntFPS_Beg = m_sp.cntScans;
                    }
                    label5.Text = String.Format("{0} Scans  ({1:F1} FPS)", m_sp.cntScans, m_fFPS);
                    textBox1.Text = String.Format("{0} Frames {1:F1} MB", m_sp.frames.Count, m_sp.frames.Count * m_sp.nNumPixels * 2D / 1024 / 1024);
                }


                label8.Text = String.Format("Pixels:{0}", m_sp.nNumPixels);
                label2.Text = String.Format("{0}", m_sp.cntTrigs); //"Com Reading";

                //整数显示坐标轴XY
                double dMinX = chartSpectrum.ChartAreas[0].AxisX.ScaleView.ViewMinimum;
                double dMaxX = chartSpectrum.ChartAreas[0].AxisX.ScaleView.ViewMaximum;
                chartSpectrum.ChartAreas[0].AxisX.IntervalOffset = -(dMinX - (((int)(dMinX / 10)) * 10));

                if (dMaxX - dMinX > 100)
                {
                    chartSpectrum.ChartAreas[0].AxisX.LabelStyle.Format = "F0";
                }
                else if (dMaxX - dMinX > 10)
                {
                    chartSpectrum.ChartAreas[0].AxisX.LabelStyle.Format = "F1";
                }
                else
                {
                    chartSpectrum.ChartAreas[0].AxisX.LabelStyle.Format = "F2";
                }

                double dMinY = chartSpectrum.ChartAreas[0].AxisY.ScaleView.ViewMinimum;
                //double dMaxY = chartSpectrum.ChartAreas[0].AxisY.ScaleView.ViewMaximum;
                // nSpan = (int)((dMaxY - dMinY) / 10);
                //if (nSpan < 10) nSpan = 10;
                //chartSpectrum.ChartAreas[0].AxisY.Interval = nSpan;
                chartSpectrum.ChartAreas[0].AxisY.IntervalOffset = -(dMinY - (((int)(dMinY / 10)) * 10));

                updateGraph();
                //updateDataGridView();

                label1.Text = String.Format("({0:F1}nm , {1:F0})", m_dIndicateX, dataProcess.WavelengthToIntensity(m_dIndicateX, m_sp.fWavelength, m_sp.fIntensity));

                //chartSpectrum.ChartAreas[0].AxisX.Interval = 100;
                //chartSpectrum.ChartAreas[0].AxisX.MajorGrid.Interval = 200;

                //logger.display(String.Format("Wavelength={0}", m_sp.fWavelength[0]));
                //if (m_bRunning)
                //ReadIntensity(m_sp.nIntUS, m_sp.nAverage, m_sp.nBoxcar);
                if (serialPort1.IsOpen || m_bOpenLAN)
                {
                    label11.Text = String.Format("S/N:{0}", m_sp.strSN);
                    label11.ForeColor = Color.Blue;
                }
                else
                {
                    label11.Text = "S/N";
                    label11.ForeColor = Color.Black;
                    ConnectSpectrometersVCP();////如果LAN和VCP都没打开，那么定时重连VCP 
                    if(!serialPort1.IsOpen)
                    {
                       // ConnectSpectrometersLAN();
                    }
                }

                if (m_bTrigMode)
                {
                    label14.Text = "Trigger Mode";
                    label14.ForeColor = Color.Blue;
                    label14.Visible = !label14.Visible;
                }
                else
                {
                    label14.Text = "Normal Mode";
                    label14.ForeColor = Color.Black;
                    label14.Visible = true;
                }

                UpdateStatusLAN();


            }
        }

        private void saveTimer_Tick(object sender, EventArgs e)
        {

        }

        ////////////////////////////////////////////////////////////////////////
        // GUI Events
        ////////////////////////////////////////////////////////////////////////

        private void numericUpDownIntegrationTimeMillisec_ValueChanged(object sender, EventArgs e) { updateSpectrometersFromGUI(); }
        private void numericUpDownScansToAverage_ValueChanged(object sender, EventArgs e) { updateSpectrometersFromGUI(); }
        private void numericUpDownSmoothingBoxcar_ValueChanged(object sender, EventArgs e) { updateSpectrometersFromGUI(); }
        private void checkBoxStrobeEnable_CheckedChanged(object sender, EventArgs e) { updateSpectrometersFromGUI(); }

        ////////////////////////////////////////////////////////////////////////
        // Save spectra
        ////////////////////////////////////////////////////////////////////////

        private void checkBoxEnableDataCollection_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxEnableDataCollection.Checked)
            {
                m_iRunning = 0x7FFFFFFF;
                updateSpectrometersFromGUI();

                listCMD.Add(0x4010); //ReadIntensityAsync(m_sp.nIntUS, m_sp.nAverage, m_sp.nBoxcar);
                EXE_listCMD();

                btnScan.Enabled = false;
            }
            else
            {
                m_iRunning = 0;
                btnScan.Enabled = true;
            }
        }

        private void buttonUnzoom_Click(object sender, EventArgs e)
        {
            chartSpectrum.ChartAreas[0].AxisX.ScaleView.ZoomReset(0);
            chartSpectrum.ChartAreas[0].AxisY.ScaleView.ZoomReset(0);
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            m_bVCP_Frist = true;

            ConnectSpectrometersVCP();
        }

        private void textBoxEventLog_TextChanged(object sender, EventArgs e)
        {

        }

        private void folderBrowserDialogMergeFolder_HelpRequest(object sender, EventArgs e)
        {

        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            m_bThreadTCP = false;//释放TCP线程

            Thread.Sleep(100);
            if (threadTCP != null)
            {
                if (threadTCP.IsAlive) threadTCP.Abort();
            }
        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            //OpenFileDialog dlg = new OpenFileDialog();
            //dlg.Title = "Open Spectrum";
            //dlg.Multiselect = true;
            //dlg.Filter = "文本文件|*.txt|csv文件|*.csv|所有文件|*.*";
            //if (dlg.ShowDialog() == DialogResult.OK)
            //{
            //    foreach (string fileName in dlg.FileNames)
            //    {
            //        Console.WriteLine("已选择文件：" + fileName);
            //    }
            //}


            //InputDialog d = new InputDialog("Connection details", "Which server:port ?", "localhost:9999");
            //if (d.ShowDialog() != DialogResult.OK)
            //{
            //    return;
            //}
            //string[] parts = d.Input.Split(':');

        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.Title = "Save Spectrum";
            dlg.FileName = DateTime.Now.ToString("yyyyMMdd-HHmmss.fff");
            dlg.Filter = "文本文件|*.txt|所有文件|*.*";
            if (dlg.ShowDialog() != DialogResult.OK) return;


            string outfileName = dlg.FileNames[0]; //foreach (string fileName in dlg.FileNames)
            using (System.IO.StreamWriter file = new System.IO.StreamWriter(outfileName))
            {
                file.WriteLine("Device S/N : {0}", m_sp.strSN);
                file.WriteLine("SampleTime : {0}", m_sp.timeStamp.ToString("yyyy-MM-dd_HHmmss.fff"));
                file.WriteLine("Integration Time : {0:F3}ms", m_sp.nIntUS / 1000D);
                file.WriteLine("Hardware Averaging : {0}", m_sp.nAverage);
                file.WriteLine("Hardware Boxcar  : {0}", m_sp.nBoxcar);

                file.Write("{0}\t{1}\t Pixels={2}", chartSpectrum.ChartAreas[0].AxisX.Title, chartSpectrum.ChartAreas[0].AxisY.Title, m_sp.nNumPixels); file.WriteLine();

                for (int i = 0; i < m_sp.nNumPixels; i++)
                {
                    file.Write("{0:f2}\t{1:f2}", m_sp.fWavelength[i], m_sp.fIntensity[i]); file.WriteLine();
                    //file.Write("{0:E6}\t{1:E6}", m_sp.fWavelength[i], m_sp.fIntensity[i]); file.WriteLine();
                }
            }
            logger.display("Save File Success!  File = {0}", outfileName);

            DialogResult result = MessageBox.Show("check the saved file?", "check file", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            if (result == DialogResult.Yes)
            {
                System.Diagnostics.Process.Start(outfileName);
            }
        }

        bool bMovingView = false;
        double PosX, PosY;
        double xMin, yMin;
        double sizeX, sizeY;

        private void chartSpectrum_MouseDown(object sender, MouseEventArgs e)
        {
            //double dX = chartSpectrum.ChartAreas[0].AxisX.PositionToValue(e.X);
            if (e.Button == MouseButtons.Left)
            {
                PosX = e.X;
                PosY = e.Y;
                //chartSpectrum.Series[nIndex].Points.Clear();
                //chartSpectrum.Series[nIndex].Points.AddXY(m_dIndicateX, -1000000);
                //chartSpectrum.Series[nIndex].Points.AddXY(m_dIndicateX, 1000000);
            }

            if (e.Button == MouseButtons.Right)//moving chart View
            {
                bMovingView = true;
                PosX = e.X;
                PosY = e.Y;
                xMin = chartSpectrum.ChartAreas[0].AxisX.ScaleView.Position;
                yMin = chartSpectrum.ChartAreas[0].AxisY.ScaleView.Position;
                sizeX = chartSpectrum.ChartAreas[0].AxisX.ScaleView.Size;
                sizeY = chartSpectrum.ChartAreas[0].AxisY.ScaleView.Size;
            }
        }
        private void chartSpectrum_MouseMove(object sender, MouseEventArgs e)
        {
            //label10.Text = "mouse moving";
            //return;

            if (bMovingView)
            {
                double dDeltaX = chartSpectrum.ChartAreas[0].AxisX.PixelPositionToValue(e.X) - chartSpectrum.ChartAreas[0].AxisX.PixelPositionToValue(PosX);
                double dDeltaY = chartSpectrum.ChartAreas[0].AxisY.PixelPositionToValue(e.Y) - chartSpectrum.ChartAreas[0].AxisY.PixelPositionToValue(PosY);
                chartSpectrum.ChartAreas[0].AxisX.ScaleView.Zoom(xMin - dDeltaX, sizeX, DateTimeIntervalType.Number);
                chartSpectrum.ChartAreas[0].AxisY.ScaleView.Zoom(yMin - dDeltaY, sizeY, DateTimeIntervalType.Number);
                //chartSpectrum.ChartAreas[0].AxisY.ScaleView.Zoom(yMin, sizeY, DateTimeIntervalType.Number);//只移动X
            }
        }
        private void chartSpectrum_MouseUP(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                bMovingView = false;
            }

            if (e.Button == MouseButtons.Left)
            {
                //改变指示器
                if (Math.Abs(e.X - PosX) < 5)
                {
                    SetIndicate(chartSpectrum.ChartAreas[0].AxisX.PixelPositionToValue(e.X));
                }

            }
        }

        private void SetIndicate(double dWavelength)
        {
            m_dIndicateX = (float)dWavelength;
            int nIndex = chartSpectrum.Series.Count - 1;//最后一条是指示条
            chartSpectrum.Series[nIndex].Points[0].XValue = m_dIndicateX;
            chartSpectrum.Series[nIndex].Points[1].XValue = m_dIndicateX;
            textBoxIndicate.Text = dWavelength.ToString("F3");
        }


        private void TabSelItemChanged(object sender, EventArgs e)
        {
            if (tabControlSettings.SelectedIndex == 0)
            {
                if (m_bTrigMode)
                {
                    //m_bTrigPara = false;
                    listCMD.Add(0x4052);
                    EXE_listCMD();
                }
            }
            if (tabControlSettings.SelectedIndex == 1)
            {
                if (!m_bTrigMode)
                {
                    //m_bTrigPara = true;
                    listCMD.Add(0x4051);
                    //EXE_listCMD();
                }

            }

            if (tabControlSettings.SelectedIndex == 2)
            {
                updateDataGridView();
            }
        }

        private void btnUpdateDataGrid_Click(object sender, EventArgs e)
        {
            updateDataGridView();
        }

        private void btnClearBuffer_Click(object sender, EventArgs e)
        {
            m_sp.frames.Clear();
            m_sp.sampleTimes.Clear();
            logger.display("Clear Buffer");
            //chartSpectrum.ChartAreas[0].AxisY.ScaleView.Zoom(20000, 40000);

        }

        private void btnSaveBuffer_Click(object sender, EventArgs e)
        {
            //TOO: Add your own code here!

        }

        private void textBoxIndicateEnter(object sender, EventArgs e)
        {

        }

        private void textBoxIndicateChanged(object sender, EventArgs e)
        {

        }

        private void btnIndicate_Click(object sender, EventArgs e)
        {

            if (m_sp.buf.Count > 0)
            {
                m_sp.buf.Clear();
            }
            if (listCMD.Count <= 0)
            {
                listCMD.Add(0x4010);
            }
            EXE_listCMD();
        }

        private void textBoxIndicateKeyDown(object sender, KeyEventArgs e)
        {
            // 判断：如果输入的是回车键
            if (e.KeyCode == Keys.Enter)
            {
                double dIndicate = Convert.ToDouble(textBoxIndicate.Text);
                SetIndicate(dIndicate);
                // 触发btn的事件
                //this.btn_Click(sender, e);
            }
        }


        TcpClient client = null;
        //private const int bufferSize = 8000;
        NetworkStream TcpStream = null;
        bool m_bThreadTCP = false;
        Thread threadTCP = null;
        IAsyncResult resultTCP;
        //public delegate void showData(string msg);

        private void TCP_Connect(String strIP, int port, int nTimeOut)
        {
            client = new TcpClient();
            
            resultTCP = client.BeginConnect(strIP, port, null, null);
            var success = resultTCP.AsyncWaitHandle.WaitOne(nTimeOut, true);//result.AsyncWaitHandle.WaitOne(TimeSpan.FromSeconds(1));
            if (success && client.Connected)// we have connected
            {
                m_bOpenLAN = true;
            }
            else
            {
                m_bOpenLAN = false;  //throw new Exception("Failed to connect.");
            }


            if (m_bOpenLAN)
            {
                TcpStream = client.GetStream();

                if (threadTCP != null)
                {
                    m_bThreadTCP = false;
                    Thread.Sleep(200);
                    if (threadTCP.IsAlive) threadTCP.Abort();
                }
                threadTCP = new Thread(TCP_Thread_Listener);
                threadTCP.IsBackground = true;//后台线程，随主程序一起结束
                m_bThreadTCP = true;
                threadTCP.Start();
            }
        }

        private void TCP_Write(byte[] data, int offset, int size)
        {
            if (m_bOpenLAN)
            {
                TcpStream.Write(data, offset, size);
            }
        }
        private void TCP_Thread_Listener()
        {
            do
            {
                try
                {
                    int readSize;

                    if (!m_bOpenLAN) continue;

                    lock (TcpStream) //不需要lock 因为就这里用到
                    {
                        readSize = TcpStream.Read(pBufIN_LAN, 0, pBufIN_LAN.Length);
                        if (readSize > 0)
                        {
                            Data_Dealer(pBufIN_LAN, readSize);
                        }
                    }
                }
                catch
                {
                    m_bOpenLAN = false;
                    return;
                }
                //将缓存中的数据写入传输流
            } while (m_bThreadTCP);
        }

        private void TCP_Close()
        {
            m_bOpenLAN = false;
            m_bThreadTCP = false;
            Thread.Sleep(200);
            if (threadTCP != null)
            {
                if (threadTCP.IsAlive) threadTCP.Abort();
            }
        }

        private void label8_Click(object sender, EventArgs e)
        {

        }

        private void label11_Click(object sender, EventArgs e)
        {

        }

        private void btnConnectLAN_Click(object sender, EventArgs e)
        {
            m_bVCP_Frist = false;
            ConnectSpectrometersLAN();

            if (m_bOpenLAN)
            {
            }
            else
            {
                MessageBox.Show("Open LAN Failed!");
                return;
            }
        }

        private void btnSetIP_Click(object sender, EventArgs e)
        {
            //listCMD.Add(0x1020);//设置IP
            //listCMD.Add(0x1021);//读取IP
        }
        //https://blog.csdn.net/qq_39569480/article/details/103471568
    }
}
