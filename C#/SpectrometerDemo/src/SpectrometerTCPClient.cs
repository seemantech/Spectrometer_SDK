

using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Threading.Tasks;
public class SpectrometerTCPClient
{
    Socket socket;
    NetworkStream tcpStream;
    
    private IAsyncResult asyncResultRead; //接收数据的异步对象
    private IAsyncResult asyncResultWrite;//发送数据的异步对象
    private byte[] buffers = new byte[0x10000];//new byte[0x1000];

    public bool bOpen = false;
    public List<Byte> buf = new List<Byte>();

    public void Connect(string strHost,int port)
    {
        Task.Factory.StartNew(() =>
        {
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            IAsyncResult conAsync = socket.BeginConnect(strHost, port, null, socket);//开始连接
            //bool success = conAsync.AsyncWaitHandle.WaitOne(6000, true);//堵塞 直到收到反馈

            bool success = conAsync.AsyncWaitHandle.WaitOne(2000, true);//堵塞 直到收到反馈
            if (success && socket.Connected)//成功连接
            {
                
                socket.EndConnect(conAsync);//关闭异步对象
                tcpStream = new NetworkStream(socket);//创建收发数据流
                socket.SetSocketOption(SocketOptionLevel.Tcp, SocketOptionName.NoDelay, true);//无延迟发送
                LAN_Receive();//开始接收
                bOpen = true;
            }
            else
            {
                //超时或者连接失败
                bOpen = false;
            }
        });
    }

    public void LAN_Receive()
    {
        try
        {
            //异步从流中读取数据
            asyncResultRead = tcpStream.BeginRead(buffers, 0, buffers.Length, EndReceive, socket);
        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }
    }

    private void EndReceive(IAsyncResult asyncReceive)
    {
        try
        {
            int len = tcpStream.EndRead(asyncReceive);
            if (len > 0)
            {
                //读取数据内容//ReadData(buffers, 0, len);
                for (int i = 0; i < len; i++ )
                {
                    buf.Add(buffers[i]);
                }

                //再次开启接收
                LAN_Receive();

                //Exe CMD List
            }
            else
            {}
        }catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }
    }
    
    //private void ReadData(byte[] bytes, int offset, int length)
    //{
    //    //在此处理接收到的数据
    //}

    //发送数据
    public void Send(byte[] bytes, int offset, int length)
    {
        try
        {
            asyncResultWrite = tcpStream.BeginWrite(bytes, offset, length, EndSend, socket);
        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }
    }
    
    private void EndSend(IAsyncResult ar)
    {
        try
        {
            tcpStream.EndWrite(ar);
        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }
    }
    //断开连接
    public void Disconnect()
    {
        try
        {
            //关闭两个异步对象
            if (!asyncResultRead.IsCompleted)
            {
                asyncResultRead.AsyncWaitHandle.Close();
            }
            if (!asyncResultWrite.IsCompleted)
            {
                asyncResultWrite.AsyncWaitHandle.Close();
            }
            tcpStream.Close();
            tcpStream.Dispose();//释放流
            socket.Shutdown(SocketShutdown.Both);//关闭发送和接收
            socket.Close();socket.Dispose();
        }
        catch (Exception e)
        {

        }
    }
}