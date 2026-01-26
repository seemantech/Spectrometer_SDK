namespace SpectrometerCSharpDemo
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea2 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend2 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            this.chartSpectrum = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.btnScan = new System.Windows.Forms.Button();
            this.checkBoxEnableIrradiance = new System.Windows.Forms.CheckBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnIndicate = new System.Windows.Forms.Button();
            this.textBoxIndicate = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.checkBoxComputeNoise = new System.Windows.Forms.CheckBox();
            this.labelSaveCount = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.checkBoxStrobeEnable = new System.Windows.Forms.CheckBox();
            this.checkBoxEnableNLC = new System.Windows.Forms.CheckBox();
            this.btnUnzoom = new System.Windows.Forms.Button();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.btnSaveBuffer = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.btnClearBuffer = new System.Windows.Forms.Button();
            this.btnConnectVCP = new System.Windows.Forms.Button();
            this.btnSave = new System.Windows.Forms.Button();
            this.checkBoxEnableDataCollection = new System.Windows.Forms.CheckBox();
            this.label5 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.tabControlSettings = new System.Windows.Forms.TabControl();
            this.tabPageAcquisition = new System.Windows.Forms.TabPage();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.btnSetIP = new System.Windows.Forms.Button();
            this.textBoxIP = new System.Windows.Forms.TextBox();
            this.labelStatusVCP = new System.Windows.Forms.Label();
            this.btnConnectLAN = new System.Windows.Forms.Button();
            this.label13 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.btnOpen = new System.Windows.Forms.Button();
            this.label11 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.IntegrationTimeMS = new System.Windows.Forms.NumericUpDown();
            this.ScansAverage = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.ScansBoxcar = new System.Windows.Forms.NumericUpDown();
            this.tabPageTrigger = new System.Windows.Forms.TabPage();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.tabPageData = new System.Windows.Forms.TabPage();
            this.btnUpdateDataGrid = new System.Windows.Forms.Button();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.tabPageLAN = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.textBoxEventLog = new System.Windows.Forms.TextBox();
            this.saveFileDialogSaveAll = new System.Windows.Forms.SaveFileDialog();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.folderBrowserDialogMergeFolder = new System.Windows.Forms.FolderBrowserDialog();
            this.splitContainerAppVsEventLog = new System.Windows.Forms.SplitContainer();
            this.splitContainerGraphSettingsVsControls = new System.Windows.Forms.SplitContainer();
            this.splitContainerGraphVsSettings = new System.Windows.Forms.SplitContainer();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.chartSpectrum)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.tabControlSettings.SuspendLayout();
            this.tabPageAcquisition.SuspendLayout();
            this.groupBox5.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.IntegrationTimeMS)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ScansAverage)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ScansBoxcar)).BeginInit();
            this.tabPageTrigger.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.tabPageData.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainerAppVsEventLog)).BeginInit();
            this.splitContainerAppVsEventLog.Panel1.SuspendLayout();
            this.splitContainerAppVsEventLog.Panel2.SuspendLayout();
            this.splitContainerAppVsEventLog.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainerGraphSettingsVsControls)).BeginInit();
            this.splitContainerGraphSettingsVsControls.Panel1.SuspendLayout();
            this.splitContainerGraphSettingsVsControls.Panel2.SuspendLayout();
            this.splitContainerGraphSettingsVsControls.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainerGraphVsSettings)).BeginInit();
            this.splitContainerGraphVsSettings.Panel1.SuspendLayout();
            this.splitContainerGraphVsSettings.Panel2.SuspendLayout();
            this.splitContainerGraphVsSettings.SuspendLayout();
            this.SuspendLayout();
            // 
            // chartSpectrum
            // 
            chartArea2.AxisX.IntervalAutoMode = System.Windows.Forms.DataVisualization.Charting.IntervalAutoMode.VariableCount;
            chartArea2.AxisX.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea2.AxisX.IsStartedFromZero = false;
            chartArea2.AxisX.MajorGrid.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dot;
            chartArea2.AxisX.Maximum = 1150D;
            chartArea2.AxisX.Minimum = 150D;
            chartArea2.AxisX.MinorGrid.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dot;
            chartArea2.AxisX.Title = "Wavelength(nm)";
            chartArea2.AxisX.TitleFont = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            chartArea2.AxisY.IntervalAutoMode = System.Windows.Forms.DataVisualization.Charting.IntervalAutoMode.VariableCount;
            chartArea2.AxisY.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea2.AxisY.IsStartedFromZero = false;
            chartArea2.AxisY.MajorGrid.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dot;
            chartArea2.AxisY.Maximum = 70000D;
            chartArea2.AxisY.Minimum = 0D;
            chartArea2.AxisY.MinorGrid.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dot;
            chartArea2.AxisY.TextOrientation = System.Windows.Forms.DataVisualization.Charting.TextOrientation.Stacked;
            chartArea2.AxisY.Title = "Intensity";
            chartArea2.AxisY.TitleFont = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            chartArea2.CursorX.Interval = 5D;
            chartArea2.CursorX.IsUserSelectionEnabled = true;
            chartArea2.CursorX.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dot;
            chartArea2.CursorY.Interval = 10D;
            chartArea2.CursorY.IsUserSelectionEnabled = true;
            chartArea2.CursorY.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dot;
            chartArea2.Name = "ChartArea1";
            this.chartSpectrum.ChartAreas.Add(chartArea2);
            this.chartSpectrum.Dock = System.Windows.Forms.DockStyle.Fill;
            legend2.Alignment = System.Drawing.StringAlignment.Center;
            legend2.Name = "Legend1";
            this.chartSpectrum.Legends.Add(legend2);
            this.chartSpectrum.Location = new System.Drawing.Point(0, 0);
            this.chartSpectrum.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.chartSpectrum.Name = "chartSpectrum";
            this.chartSpectrum.Size = new System.Drawing.Size(1110, 411);
            this.chartSpectrum.TabIndex = 0;
            this.chartSpectrum.Text = "Spectrum";
            this.chartSpectrum.MouseDown += new System.Windows.Forms.MouseEventHandler(this.chartSpectrum_MouseDown);
            this.chartSpectrum.MouseMove += new System.Windows.Forms.MouseEventHandler(this.chartSpectrum_MouseMove);
            this.chartSpectrum.MouseUp += new System.Windows.Forms.MouseEventHandler(this.chartSpectrum_MouseUP);
            // 
            // btnScan
            // 
            this.btnScan.Enabled = false;
            this.btnScan.Location = new System.Drawing.Point(3, 278);
            this.btnScan.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnScan.Name = "btnScan";
            this.btnScan.Size = new System.Drawing.Size(86, 22);
            this.btnScan.TabIndex = 1;
            this.btnScan.Text = "Single Scan";
            this.btnScan.UseVisualStyleBackColor = true;
            this.btnScan.Click += new System.EventHandler(this.btnScan_Click);
            // 
            // checkBoxEnableIrradiance
            // 
            this.checkBoxEnableIrradiance.AutoSize = true;
            this.checkBoxEnableIrradiance.Location = new System.Drawing.Point(760, 59);
            this.checkBoxEnableIrradiance.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.checkBoxEnableIrradiance.Name = "checkBoxEnableIrradiance";
            this.checkBoxEnableIrradiance.Size = new System.Drawing.Size(120, 16);
            this.checkBoxEnableIrradiance.TabIndex = 2;
            this.checkBoxEnableIrradiance.Text = "Apply Irradiance";
            this.checkBoxEnableIrradiance.UseVisualStyleBackColor = true;
            this.checkBoxEnableIrradiance.Visible = false;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.checkBoxStrobeEnable);
            this.groupBox1.Controls.Add(this.btnIndicate);
            this.groupBox1.Controls.Add(this.checkBoxEnableIrradiance);
            this.groupBox1.Controls.Add(this.textBoxIndicate);
            this.groupBox1.Controls.Add(this.label10);
            this.groupBox1.Controls.Add(this.checkBoxComputeNoise);
            this.groupBox1.Controls.Add(this.labelSaveCount);
            this.groupBox1.Controls.Add(this.label14);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.groupBox9);
            this.groupBox1.Controls.Add(this.checkBoxEnableNLC);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox1.Location = new System.Drawing.Point(0, 0);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox1.Size = new System.Drawing.Size(1455, 117);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Status";
            // 
            // btnIndicate
            // 
            this.btnIndicate.Location = new System.Drawing.Point(695, 22);
            this.btnIndicate.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnIndicate.Name = "btnIndicate";
            this.btnIndicate.Size = new System.Drawing.Size(49, 29);
            this.btnIndicate.TabIndex = 28;
            this.btnIndicate.Text = "Retry";
            this.btnIndicate.UseVisualStyleBackColor = true;
            this.btnIndicate.Visible = false;
            this.btnIndicate.Click += new System.EventHandler(this.btnIndicate_Click);
            // 
            // textBoxIndicate
            // 
            this.textBoxIndicate.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBoxIndicate.ForeColor = System.Drawing.Color.Purple;
            this.textBoxIndicate.Location = new System.Drawing.Point(434, 7);
            this.textBoxIndicate.Name = "textBoxIndicate";
            this.textBoxIndicate.Size = new System.Drawing.Size(79, 26);
            this.textBoxIndicate.TabIndex = 28;
            this.textBoxIndicate.Text = "600.000";
            this.textBoxIndicate.TextChanged += new System.EventHandler(this.textBoxIndicateChanged);
            this.textBoxIndicate.Enter += new System.EventHandler(this.textBoxIndicateEnter);
            this.textBoxIndicate.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBoxIndicateKeyDown);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(519, 12);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(59, 12);
            this.label10.TabIndex = 10;
            this.label10.Text = "Buffers：";
            this.label10.Visible = false;
            // 
            // checkBoxComputeNoise
            // 
            this.checkBoxComputeNoise.AutoSize = true;
            this.checkBoxComputeNoise.Location = new System.Drawing.Point(925, 29);
            this.checkBoxComputeNoise.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.checkBoxComputeNoise.Name = "checkBoxComputeNoise";
            this.checkBoxComputeNoise.Size = new System.Drawing.Size(102, 16);
            this.checkBoxComputeNoise.TabIndex = 1;
            this.checkBoxComputeNoise.Text = "Compute Noise";
            this.checkBoxComputeNoise.UseVisualStyleBackColor = true;
            this.checkBoxComputeNoise.Visible = false;
            // 
            // labelSaveCount
            // 
            this.labelSaveCount.Font = new System.Drawing.Font("Lucida Console", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelSaveCount.ForeColor = System.Drawing.Color.Green;
            this.labelSaveCount.Location = new System.Drawing.Point(474, 49);
            this.labelSaveCount.Name = "labelSaveCount";
            this.labelSaveCount.Size = new System.Drawing.Size(78, 17);
            this.labelSaveCount.TabIndex = 11;
            this.labelSaveCount.Text = "0";
            this.labelSaveCount.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.labelSaveCount.Visible = false;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label14.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(192)))));
            this.label14.Location = new System.Drawing.Point(233, 50);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(140, 25);
            this.label14.TabIndex = 22;
            this.label14.Text = "Trigger Mode";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(0)))), ((int)(((byte)(192)))));
            this.label1.Location = new System.Drawing.Point(233, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(187, 25);
            this.label1.TabIndex = 13;
            this.label1.Text = "(500.00nm,10000)";
            // 
            // groupBox9
            // 
            this.groupBox9.Location = new System.Drawing.Point(35, 49);
            this.groupBox9.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox9.Name = "groupBox9";
            this.groupBox9.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox9.Size = new System.Drawing.Size(129, 66);
            this.groupBox9.TabIndex = 8;
            this.groupBox9.TabStop = false;
            this.groupBox9.Text = "Advanced Features";
            this.groupBox9.Visible = false;
            // 
            // checkBoxStrobeEnable
            // 
            this.checkBoxStrobeEnable.AutoSize = true;
            this.checkBoxStrobeEnable.Location = new System.Drawing.Point(587, 43);
            this.checkBoxStrobeEnable.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.checkBoxStrobeEnable.Name = "checkBoxStrobeEnable";
            this.checkBoxStrobeEnable.Size = new System.Drawing.Size(102, 16);
            this.checkBoxStrobeEnable.TabIndex = 3;
            this.checkBoxStrobeEnable.Text = "Strobe Enable";
            this.checkBoxStrobeEnable.UseVisualStyleBackColor = true;
            this.checkBoxStrobeEnable.Visible = false;
            this.checkBoxStrobeEnable.CheckedChanged += new System.EventHandler(this.checkBoxStrobeEnable_CheckedChanged);
            // 
            // checkBoxEnableNLC
            // 
            this.checkBoxEnableNLC.AutoSize = true;
            this.checkBoxEnableNLC.Checked = true;
            this.checkBoxEnableNLC.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxEnableNLC.Location = new System.Drawing.Point(925, 49);
            this.checkBoxEnableNLC.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.checkBoxEnableNLC.Name = "checkBoxEnableNLC";
            this.checkBoxEnableNLC.Size = new System.Drawing.Size(42, 16);
            this.checkBoxEnableNLC.TabIndex = 21;
            this.checkBoxEnableNLC.Text = "NLC";
            this.checkBoxEnableNLC.UseVisualStyleBackColor = true;
            this.checkBoxEnableNLC.Visible = false;
            // 
            // btnUnzoom
            // 
            this.btnUnzoom.Location = new System.Drawing.Point(3, 360);
            this.btnUnzoom.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnUnzoom.Name = "btnUnzoom";
            this.btnUnzoom.Size = new System.Drawing.Size(86, 22);
            this.btnUnzoom.TabIndex = 5;
            this.btnUnzoom.Text = "UnzoomXY";
            this.btnUnzoom.UseVisualStyleBackColor = true;
            this.btnUnzoom.Click += new System.EventHandler(this.buttonUnzoom_Click);
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.btnSaveBuffer);
            this.groupBox8.Controls.Add(this.textBox1);
            this.groupBox8.Controls.Add(this.btnClearBuffer);
            this.groupBox8.Location = new System.Drawing.Point(6, 390);
            this.groupBox8.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox8.Size = new System.Drawing.Size(144, 91);
            this.groupBox8.TabIndex = 7;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "RAM Buffers";
            // 
            // btnSaveBuffer
            // 
            this.btnSaveBuffer.Location = new System.Drawing.Point(58, 51);
            this.btnSaveBuffer.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnSaveBuffer.Name = "btnSaveBuffer";
            this.btnSaveBuffer.Size = new System.Drawing.Size(83, 24);
            this.btnSaveBuffer.TabIndex = 27;
            this.btnSaveBuffer.Text = "Save...";
            this.btnSaveBuffer.UseVisualStyleBackColor = true;
            this.btnSaveBuffer.Click += new System.EventHandler(this.btnSaveBuffer_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(6, 25);
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(135, 21);
            this.textBox1.TabIndex = 23;
            // 
            // btnClearBuffer
            // 
            this.btnClearBuffer.Location = new System.Drawing.Point(6, 51);
            this.btnClearBuffer.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnClearBuffer.Name = "btnClearBuffer";
            this.btnClearBuffer.Size = new System.Drawing.Size(49, 24);
            this.btnClearBuffer.TabIndex = 26;
            this.btnClearBuffer.Text = "Clear";
            this.btnClearBuffer.UseVisualStyleBackColor = true;
            this.btnClearBuffer.Click += new System.EventHandler(this.btnClearBuffer_Click);
            // 
            // btnConnectVCP
            // 
            this.btnConnectVCP.Location = new System.Drawing.Point(147, 120);
            this.btnConnectVCP.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnConnectVCP.Name = "btnConnectVCP";
            this.btnConnectVCP.Size = new System.Drawing.Size(86, 22);
            this.btnConnectVCP.TabIndex = 6;
            this.btnConnectVCP.Text = "Connect VCP";
            this.btnConnectVCP.UseVisualStyleBackColor = true;
            this.btnConnectVCP.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // btnSave
            // 
            this.btnSave.Location = new System.Drawing.Point(3, 332);
            this.btnSave.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(86, 24);
            this.btnSave.TabIndex = 3;
            this.btnSave.Text = "Save...";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.buttonSave_Click);
            // 
            // checkBoxEnableDataCollection
            // 
            this.checkBoxEnableDataCollection.AutoSize = true;
            this.checkBoxEnableDataCollection.Checked = true;
            this.checkBoxEnableDataCollection.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxEnableDataCollection.Location = new System.Drawing.Point(6, 254);
            this.checkBoxEnableDataCollection.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.checkBoxEnableDataCollection.Name = "checkBoxEnableDataCollection";
            this.checkBoxEnableDataCollection.Size = new System.Drawing.Size(66, 16);
            this.checkBoxEnableDataCollection.TabIndex = 3;
            this.checkBoxEnableDataCollection.Text = "Running";
            this.checkBoxEnableDataCollection.UseVisualStyleBackColor = true;
            this.checkBoxEnableDataCollection.CheckedChanged += new System.EventHandler(this.checkBoxEnableDataCollection_CheckedChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 308);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(47, 12);
            this.label5.TabIndex = 14;
            this.label5.Text = "0 Scans";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.tabControlSettings);
            this.groupBox2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox2.Location = new System.Drawing.Point(0, 0);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox2.Size = new System.Drawing.Size(341, 411);
            this.groupBox2.TabIndex = 4;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "ControlPanel";
            // 
            // tabControlSettings
            // 
            this.tabControlSettings.Controls.Add(this.tabPageAcquisition);
            this.tabControlSettings.Controls.Add(this.tabPageTrigger);
            this.tabControlSettings.Controls.Add(this.tabPageData);
            this.tabControlSettings.Controls.Add(this.tabPageLAN);
            this.tabControlSettings.Controls.Add(this.tabPage2);
            this.tabControlSettings.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControlSettings.Location = new System.Drawing.Point(3, 16);
            this.tabControlSettings.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tabControlSettings.Name = "tabControlSettings";
            this.tabControlSettings.SelectedIndex = 0;
            this.tabControlSettings.Size = new System.Drawing.Size(335, 393);
            this.tabControlSettings.TabIndex = 21;
            this.tabControlSettings.SelectedIndexChanged += new System.EventHandler(this.TabSelItemChanged);
            // 
            // tabPageAcquisition
            // 
            this.tabPageAcquisition.Controls.Add(this.groupBox5);
            this.tabPageAcquisition.Location = new System.Drawing.Point(4, 22);
            this.tabPageAcquisition.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tabPageAcquisition.Name = "tabPageAcquisition";
            this.tabPageAcquisition.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tabPageAcquisition.Size = new System.Drawing.Size(327, 367);
            this.tabPageAcquisition.TabIndex = 1;
            this.tabPageAcquisition.Text = "Acquisition";
            this.tabPageAcquisition.UseVisualStyleBackColor = true;
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.btnSetIP);
            this.groupBox5.Controls.Add(this.textBoxIP);
            this.groupBox5.Controls.Add(this.labelStatusVCP);
            this.groupBox5.Controls.Add(this.btnConnectLAN);
            this.groupBox5.Controls.Add(this.label13);
            this.groupBox5.Controls.Add(this.label12);
            this.groupBox5.Controls.Add(this.btnOpen);
            this.groupBox5.Controls.Add(this.label11);
            this.groupBox5.Controls.Add(this.label5);
            this.groupBox5.Controls.Add(this.label8);
            this.groupBox5.Controls.Add(this.btnUnzoom);
            this.groupBox5.Controls.Add(this.btnSave);
            this.groupBox5.Controls.Add(this.groupBox8);
            this.groupBox5.Controls.Add(this.btnConnectVCP);
            this.groupBox5.Controls.Add(this.label6);
            this.groupBox5.Controls.Add(this.checkBoxEnableDataCollection);
            this.groupBox5.Controls.Add(this.label9);
            this.groupBox5.Controls.Add(this.btnScan);
            this.groupBox5.Controls.Add(this.IntegrationTimeMS);
            this.groupBox5.Controls.Add(this.ScansAverage);
            this.groupBox5.Controls.Add(this.label3);
            this.groupBox5.Controls.Add(this.label7);
            this.groupBox5.Controls.Add(this.ScansBoxcar);
            this.groupBox5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox5.Location = new System.Drawing.Point(3, 2);
            this.groupBox5.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox5.Size = new System.Drawing.Size(321, 363);
            this.groupBox5.TabIndex = 19;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Acquisition";
            // 
            // btnSetIP
            // 
            this.btnSetIP.Location = new System.Drawing.Point(242, 155);
            this.btnSetIP.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnSetIP.Name = "btnSetIP";
            this.btnSetIP.Size = new System.Drawing.Size(86, 22);
            this.btnSetIP.TabIndex = 30;
            this.btnSetIP.Text = "Set IP...";
            this.btnSetIP.UseVisualStyleBackColor = true;
            this.btnSetIP.Click += new System.EventHandler(this.btnSetIP_Click);
            // 
            // textBoxIP
            // 
            this.textBoxIP.Font = new System.Drawing.Font("宋体", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBoxIP.ForeColor = System.Drawing.Color.Red;
            this.textBoxIP.Location = new System.Drawing.Point(6, 156);
            this.textBoxIP.Name = "textBoxIP";
            this.textBoxIP.Size = new System.Drawing.Size(135, 22);
            this.textBoxIP.TabIndex = 29;
            this.textBoxIP.Text = "192.168.31.177";
            // 
            // labelStatusVCP
            // 
            this.labelStatusVCP.AutoSize = true;
            this.labelStatusVCP.ForeColor = System.Drawing.Color.Red;
            this.labelStatusVCP.Location = new System.Drawing.Point(6, 125);
            this.labelStatusVCP.Name = "labelStatusVCP";
            this.labelStatusVCP.Size = new System.Drawing.Size(71, 12);
            this.labelStatusVCP.TabIndex = 27;
            this.labelStatusVCP.Text = "unconnected";
            // 
            // btnConnectLAN
            // 
            this.btnConnectLAN.Location = new System.Drawing.Point(147, 156);
            this.btnConnectLAN.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnConnectLAN.Name = "btnConnectLAN";
            this.btnConnectLAN.Size = new System.Drawing.Size(86, 22);
            this.btnConnectLAN.TabIndex = 26;
            this.btnConnectLAN.Text = "Connect LAN";
            this.btnConnectLAN.UseVisualStyleBackColor = true;
            this.btnConnectLAN.Click += new System.EventHandler(this.btnConnectLAN_Click);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(8, 87);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(53, 12);
            this.label13.TabIndex = 25;
            this.label13.Text = "Boxcar  ";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(8, 44);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(53, 12);
            this.label12.TabIndex = 24;
            this.label12.Text = "Hardware\r\n";
            // 
            // btnOpen
            // 
            this.btnOpen.Location = new System.Drawing.Point(190, 354);
            this.btnOpen.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnOpen.Name = "btnOpen";
            this.btnOpen.Size = new System.Drawing.Size(86, 24);
            this.btnOpen.TabIndex = 23;
            this.btnOpen.Text = "Open...";
            this.btnOpen.UseVisualStyleBackColor = true;
            this.btnOpen.Visible = false;
            this.btnOpen.Click += new System.EventHandler(this.btnOpen_Click);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(6, 202);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(23, 12);
            this.label11.TabIndex = 22;
            this.label11.Text = "S/N";
            this.label11.Click += new System.EventHandler(this.label11_Click);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 229);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(47, 12);
            this.label8.TabIndex = 22;
            this.label8.Text = "Pixels:";
            this.label8.Click += new System.EventHandler(this.label8_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(169, 20);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(17, 12);
            this.label6.TabIndex = 15;
            this.label6.Text = "ms";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(8, 20);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(47, 12);
            this.label9.TabIndex = 14;
            this.label9.Text = "IntTime";
            // 
            // IntegrationTimeMS
            // 
            this.IntegrationTimeMS.DecimalPlaces = 3;
            this.IntegrationTimeMS.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.IntegrationTimeMS.Location = new System.Drawing.Point(79, 15);
            this.IntegrationTimeMS.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.IntegrationTimeMS.Maximum = new decimal(new int[] {
            60000,
            0,
            0,
            0});
            this.IntegrationTimeMS.Name = "IntegrationTimeMS";
            this.IntegrationTimeMS.Size = new System.Drawing.Size(84, 23);
            this.IntegrationTimeMS.TabIndex = 6;
            this.IntegrationTimeMS.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.IntegrationTimeMS.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.IntegrationTimeMS.ValueChanged += new System.EventHandler(this.numericUpDownIntegrationTimeMillisec_ValueChanged);
            // 
            // ScansAverage
            // 
            this.ScansAverage.Location = new System.Drawing.Point(79, 47);
            this.ScansAverage.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.ScansAverage.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.ScansAverage.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ScansAverage.Name = "ScansAverage";
            this.ScansAverage.Size = new System.Drawing.Size(84, 21);
            this.ScansAverage.TabIndex = 18;
            this.ScansAverage.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.ScansAverage.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ScansAverage.ValueChanged += new System.EventHandler(this.numericUpDownScansToAverage_ValueChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(8, 56);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(59, 12);
            this.label3.TabIndex = 19;
            this.label3.Text = "Averaging";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(8, 75);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(53, 12);
            this.label7.TabIndex = 15;
            this.label7.Text = "Hardware";
            // 
            // ScansBoxcar
            // 
            this.ScansBoxcar.Location = new System.Drawing.Point(79, 78);
            this.ScansBoxcar.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.ScansBoxcar.Name = "ScansBoxcar";
            this.ScansBoxcar.Size = new System.Drawing.Size(84, 21);
            this.ScansBoxcar.TabIndex = 14;
            this.ScansBoxcar.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.ScansBoxcar.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ScansBoxcar.ValueChanged += new System.EventHandler(this.numericUpDownSmoothingBoxcar_ValueChanged);
            // 
            // tabPageTrigger
            // 
            this.tabPageTrigger.Controls.Add(this.groupBox4);
            this.tabPageTrigger.Location = new System.Drawing.Point(4, 22);
            this.tabPageTrigger.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tabPageTrigger.Name = "tabPageTrigger";
            this.tabPageTrigger.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tabPageTrigger.Size = new System.Drawing.Size(327, 367);
            this.tabPageTrigger.TabIndex = 0;
            this.tabPageTrigger.Text = "Trigger Mode";
            this.tabPageTrigger.UseVisualStyleBackColor = true;
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.label4);
            this.groupBox4.Controls.Add(this.label2);
            this.groupBox4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox4.Location = new System.Drawing.Point(3, 2);
            this.groupBox4.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox4.Size = new System.Drawing.Size(321, 363);
            this.groupBox4.TabIndex = 20;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Trigger";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(3, 57);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(89, 12);
            this.label4.TabIndex = 11;
            this.label4.Text = "Trigger Times:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("宋体", 21.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(192)))));
            this.label2.Location = new System.Drawing.Point(100, 47);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(118, 29);
            this.label2.TabIndex = 3;
            this.label2.Text = "Trigger";
            // 
            // tabPageData
            // 
            this.tabPageData.Controls.Add(this.btnUpdateDataGrid);
            this.tabPageData.Controls.Add(this.dataGridView1);
            this.tabPageData.Location = new System.Drawing.Point(4, 22);
            this.tabPageData.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tabPageData.Name = "tabPageData";
            this.tabPageData.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tabPageData.Size = new System.Drawing.Size(327, 367);
            this.tabPageData.TabIndex = 2;
            this.tabPageData.Text = "Data";
            this.tabPageData.UseVisualStyleBackColor = true;
            // 
            // btnUpdateDataGrid
            // 
            this.btnUpdateDataGrid.Location = new System.Drawing.Point(222, 17);
            this.btnUpdateDataGrid.Name = "btnUpdateDataGrid";
            this.btnUpdateDataGrid.Size = new System.Drawing.Size(75, 23);
            this.btnUpdateDataGrid.TabIndex = 23;
            this.btnUpdateDataGrid.Text = "Refresh";
            this.btnUpdateDataGrid.UseVisualStyleBackColor = true;
            this.btnUpdateDataGrid.Click += new System.EventHandler(this.btnUpdateDataGrid_Click);
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Dock = System.Windows.Forms.DockStyle.Left;
            this.dataGridView1.Location = new System.Drawing.Point(3, 2);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowTemplate.Height = 23;
            this.dataGridView1.Size = new System.Drawing.Size(213, 363);
            this.dataGridView1.TabIndex = 0;
            // 
            // tabPageLAN
            // 
            this.tabPageLAN.Location = new System.Drawing.Point(4, 22);
            this.tabPageLAN.Name = "tabPageLAN";
            this.tabPageLAN.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageLAN.Size = new System.Drawing.Size(327, 367);
            this.tabPageLAN.TabIndex = 3;
            this.tabPageLAN.Text = "LAN/WIFI";
            this.tabPageLAN.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Size = new System.Drawing.Size(327, 367);
            this.tabPage2.TabIndex = 4;
            this.tabPage2.Text = "USER";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // groupBox3
            // 
            this.groupBox3.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox3.Controls.Add(this.textBoxEventLog);
            this.groupBox3.Location = new System.Drawing.Point(6, 2);
            this.groupBox3.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox3.Size = new System.Drawing.Size(1446, 97);
            this.groupBox3.TabIndex = 5;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Event Log";
            // 
            // textBoxEventLog
            // 
            this.textBoxEventLog.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxEventLog.Location = new System.Drawing.Point(6, 18);
            this.textBoxEventLog.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBoxEventLog.Multiline = true;
            this.textBoxEventLog.Name = "textBoxEventLog";
            this.textBoxEventLog.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBoxEventLog.Size = new System.Drawing.Size(1434, 74);
            this.textBoxEventLog.TabIndex = 0;
            this.textBoxEventLog.TextChanged += new System.EventHandler(this.textBoxEventLog_TextChanged);
            // 
            // saveFileDialogSaveAll
            // 
            this.saveFileDialogSaveAll.Title = "Save All Acquisitions";
            // 
            // toolTip1
            // 
            this.toolTip1.IsBalloon = true;
            // 
            // folderBrowserDialogMergeFolder
            // 
            this.folderBrowserDialogMergeFolder.ShowNewFolderButton = false;
            this.folderBrowserDialogMergeFolder.HelpRequest += new System.EventHandler(this.folderBrowserDialogMergeFolder_HelpRequest);
            // 
            // splitContainerAppVsEventLog
            // 
            this.splitContainerAppVsEventLog.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.splitContainerAppVsEventLog.Location = new System.Drawing.Point(12, 11);
            this.splitContainerAppVsEventLog.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.splitContainerAppVsEventLog.Name = "splitContainerAppVsEventLog";
            this.splitContainerAppVsEventLog.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainerAppVsEventLog.Panel1
            // 
            this.splitContainerAppVsEventLog.Panel1.Controls.Add(this.splitContainerGraphSettingsVsControls);
            // 
            // splitContainerAppVsEventLog.Panel2
            // 
            this.splitContainerAppVsEventLog.Panel2.Controls.Add(this.groupBox3);
            this.splitContainerAppVsEventLog.Size = new System.Drawing.Size(1455, 639);
            this.splitContainerAppVsEventLog.SplitterDistance = 532;
            this.splitContainerAppVsEventLog.TabIndex = 6;
            // 
            // splitContainerGraphSettingsVsControls
            // 
            this.splitContainerGraphSettingsVsControls.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainerGraphSettingsVsControls.Location = new System.Drawing.Point(0, 0);
            this.splitContainerGraphSettingsVsControls.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.splitContainerGraphSettingsVsControls.Name = "splitContainerGraphSettingsVsControls";
            this.splitContainerGraphSettingsVsControls.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainerGraphSettingsVsControls.Panel1
            // 
            this.splitContainerGraphSettingsVsControls.Panel1.Controls.Add(this.splitContainerGraphVsSettings);
            // 
            // splitContainerGraphSettingsVsControls.Panel2
            // 
            this.splitContainerGraphSettingsVsControls.Panel2.Controls.Add(this.groupBox1);
            this.splitContainerGraphSettingsVsControls.Size = new System.Drawing.Size(1455, 532);
            this.splitContainerGraphSettingsVsControls.SplitterDistance = 411;
            this.splitContainerGraphSettingsVsControls.TabIndex = 6;
            // 
            // splitContainerGraphVsSettings
            // 
            this.splitContainerGraphVsSettings.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainerGraphVsSettings.Location = new System.Drawing.Point(0, 0);
            this.splitContainerGraphVsSettings.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.splitContainerGraphVsSettings.Name = "splitContainerGraphVsSettings";
            // 
            // splitContainerGraphVsSettings.Panel1
            // 
            this.splitContainerGraphVsSettings.Panel1.Controls.Add(this.chartSpectrum);
            // 
            // splitContainerGraphVsSettings.Panel2
            // 
            this.splitContainerGraphVsSettings.Panel2.Controls.Add(this.groupBox2);
            this.splitContainerGraphVsSettings.Size = new System.Drawing.Size(1455, 411);
            this.splitContainerGraphVsSettings.SplitterDistance = 1110;
            this.splitContainerGraphVsSettings.TabIndex = 5;
            // 
            // serialPort1
            // 
            this.serialPort1.BaudRate = 115200;
            this.serialPort1.ReadBufferSize = 262144;
            this.serialPort1.WriteBufferSize = 4096;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1479, 660);
            this.Controls.Add(this.splitContainerAppVsEventLog);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "Form1";
            this.Text = "Spectrometer C# Demo";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.chartSpectrum)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox8.ResumeLayout(false);
            this.groupBox8.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.tabControlSettings.ResumeLayout(false);
            this.tabPageAcquisition.ResumeLayout(false);
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.IntegrationTimeMS)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ScansAverage)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ScansBoxcar)).EndInit();
            this.tabPageTrigger.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.tabPageData.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.splitContainerAppVsEventLog.Panel1.ResumeLayout(false);
            this.splitContainerAppVsEventLog.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainerAppVsEventLog)).EndInit();
            this.splitContainerAppVsEventLog.ResumeLayout(false);
            this.splitContainerGraphSettingsVsControls.Panel1.ResumeLayout(false);
            this.splitContainerGraphSettingsVsControls.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainerGraphSettingsVsControls)).EndInit();
            this.splitContainerGraphSettingsVsControls.ResumeLayout(false);
            this.splitContainerGraphVsSettings.Panel1.ResumeLayout(false);
            this.splitContainerGraphVsSettings.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainerGraphVsSettings)).EndInit();
            this.splitContainerGraphVsSettings.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataVisualization.Charting.Chart chartSpectrum;
        private System.Windows.Forms.Button btnScan;
        private System.Windows.Forms.CheckBox checkBoxEnableIrradiance;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TextBox textBoxEventLog;
        private System.Windows.Forms.CheckBox checkBoxEnableDataCollection;
        private System.Windows.Forms.SaveFileDialog saveFileDialogSaveAll;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.Button btnUnzoom;
        private System.Windows.Forms.Button btnConnectVCP;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialogMergeFolder;
        private System.Windows.Forms.GroupBox groupBox9;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label labelSaveCount;
        private System.Windows.Forms.SplitContainer splitContainerAppVsEventLog;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox checkBoxStrobeEnable;
        private System.Windows.Forms.SplitContainer splitContainerGraphVsSettings;
        private System.Windows.Forms.SplitContainer splitContainerGraphSettingsVsControls;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TabControl tabControlSettings;
        private System.Windows.Forms.TabPage tabPageAcquisition;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.CheckBox checkBoxEnableNLC;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.NumericUpDown IntegrationTimeMS;
        private System.Windows.Forms.NumericUpDown ScansAverage;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.NumericUpDown ScansBoxcar;
        private System.Windows.Forms.TabPage tabPageTrigger;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TabPage tabPageData;
        private System.Windows.Forms.CheckBox checkBoxComputeNoise;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TabPage tabPageLAN;
        private System.Windows.Forms.Button btnOpen;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.Button btnUpdateDataGrid;
        private System.Windows.Forms.Button btnSaveBuffer;
        private System.Windows.Forms.Button btnClearBuffer;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBoxIndicate;
        private System.Windows.Forms.Button btnIndicate;
        private System.Windows.Forms.Label labelStatusVCP;
        private System.Windows.Forms.Button btnConnectLAN;
        private System.Windows.Forms.TextBox textBoxIP;
        private System.Windows.Forms.Button btnSetIP;
    }
}

