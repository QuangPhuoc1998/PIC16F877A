namespace VS_Giao_tiep_may_tinh
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.cbStop = new System.Windows.Forms.ComboBox();
            this.cbParity = new System.Windows.Forms.ComboBox();
            this.cbData = new System.Windows.Forms.ComboBox();
            this.cbBaud = new System.Windows.Forms.ComboBox();
            this.cbCom = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btThoat = new System.Windows.Forms.Button();
            this.btNgat = new System.Windows.Forms.Button();
            this.btXoa = new System.Windows.Forms.Button();
            this.btKetnoi = new System.Windows.Forms.Button();
            this.txtDulieu = new System.Windows.Forms.TextBox();
            this.btStart = new System.Windows.Forms.Button();
            this.btCompact = new System.Windows.Forms.Button();
            this.btExit = new System.Windows.Forms.Button();
            this.zedGraphControl1 = new ZedGraph.ZedGraphControl();
            this.txtNumberData = new System.Windows.Forms.GroupBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.txtNumberData.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.cbStop);
            this.groupBox1.Controls.Add(this.cbParity);
            this.groupBox1.Controls.Add(this.cbData);
            this.groupBox1.Controls.Add(this.cbBaud);
            this.groupBox1.Controls.Add(this.cbCom);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(33, 33);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(294, 244);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Bảng điều khiển";
            // 
            // cbStop
            // 
            this.cbStop.FormattingEnabled = true;
            this.cbStop.Location = new System.Drawing.Point(146, 198);
            this.cbStop.Name = "cbStop";
            this.cbStop.Size = new System.Drawing.Size(125, 24);
            this.cbStop.TabIndex = 1;
            this.cbStop.SelectedIndexChanged += new System.EventHandler(this.cbStop_SelectedIndexChanged);
            // 
            // cbParity
            // 
            this.cbParity.FormattingEnabled = true;
            this.cbParity.Location = new System.Drawing.Point(146, 155);
            this.cbParity.Name = "cbParity";
            this.cbParity.Size = new System.Drawing.Size(125, 24);
            this.cbParity.TabIndex = 1;
            this.cbParity.SelectedIndexChanged += new System.EventHandler(this.cbParity_SelectedIndexChanged);
            // 
            // cbData
            // 
            this.cbData.FormattingEnabled = true;
            this.cbData.Location = new System.Drawing.Point(146, 116);
            this.cbData.Name = "cbData";
            this.cbData.Size = new System.Drawing.Size(125, 24);
            this.cbData.TabIndex = 1;
            this.cbData.SelectedIndexChanged += new System.EventHandler(this.cbData_SelectedIndexChanged);
            // 
            // cbBaud
            // 
            this.cbBaud.FormattingEnabled = true;
            this.cbBaud.Location = new System.Drawing.Point(146, 74);
            this.cbBaud.Name = "cbBaud";
            this.cbBaud.Size = new System.Drawing.Size(125, 24);
            this.cbBaud.TabIndex = 1;
            this.cbBaud.SelectedIndexChanged += new System.EventHandler(this.cbBaud_SelectedIndexChanged);
            // 
            // cbCom
            // 
            this.cbCom.FormattingEnabled = true;
            this.cbCom.Location = new System.Drawing.Point(146, 38);
            this.cbCom.Name = "cbCom";
            this.cbCom.Size = new System.Drawing.Size(125, 24);
            this.cbCom.TabIndex = 1;
            this.cbCom.SelectedIndexChanged += new System.EventHandler(this.cbCom_SelectedIndexChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(17, 205);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(56, 17);
            this.label5.TabIndex = 0;
            this.label5.Text = "Stop bit";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(17, 162);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(44, 17);
            this.label4.TabIndex = 0;
            this.label4.Text = "Parity";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(17, 123);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(57, 17);
            this.label3.TabIndex = 0;
            this.label3.Text = "Data bit";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(17, 81);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(71, 17);
            this.label2.TabIndex = 0;
            this.label2.Text = "BaudRate";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(17, 38);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(76, 17);
            this.label1.TabIndex = 0;
            this.label1.Text = "Cổng COM";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.btThoat);
            this.groupBox2.Controls.Add(this.btNgat);
            this.groupBox2.Controls.Add(this.btXoa);
            this.groupBox2.Controls.Add(this.btKetnoi);
            this.groupBox2.Location = new System.Drawing.Point(38, 297);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(289, 142);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            // 
            // btThoat
            // 
            this.btThoat.Location = new System.Drawing.Point(156, 90);
            this.btThoat.Name = "btThoat";
            this.btThoat.Size = new System.Drawing.Size(99, 31);
            this.btThoat.TabIndex = 0;
            this.btThoat.Text = "Thoát";
            this.btThoat.UseVisualStyleBackColor = true;
            this.btThoat.Click += new System.EventHandler(this.btThoat_Click);
            // 
            // btNgat
            // 
            this.btNgat.Location = new System.Drawing.Point(156, 25);
            this.btNgat.Name = "btNgat";
            this.btNgat.Size = new System.Drawing.Size(99, 31);
            this.btNgat.TabIndex = 0;
            this.btNgat.Text = "Ngắt";
            this.btNgat.UseVisualStyleBackColor = true;
            this.btNgat.Click += new System.EventHandler(this.btNgat_Click);
            // 
            // btXoa
            // 
            this.btXoa.Location = new System.Drawing.Point(12, 90);
            this.btXoa.Name = "btXoa";
            this.btXoa.Size = new System.Drawing.Size(99, 31);
            this.btXoa.TabIndex = 0;
            this.btXoa.Text = "Xóa";
            this.btXoa.UseVisualStyleBackColor = true;
            this.btXoa.Click += new System.EventHandler(this.btXoa_Click);
            // 
            // btKetnoi
            // 
            this.btKetnoi.Location = new System.Drawing.Point(12, 25);
            this.btKetnoi.Name = "btKetnoi";
            this.btKetnoi.Size = new System.Drawing.Size(99, 31);
            this.btKetnoi.TabIndex = 0;
            this.btKetnoi.Text = "Kết nối";
            this.btKetnoi.UseVisualStyleBackColor = true;
            this.btKetnoi.Click += new System.EventHandler(this.btKetnoi_Click);
            // 
            // txtDulieu
            // 
            this.txtDulieu.Location = new System.Drawing.Point(35, 36);
            this.txtDulieu.Multiline = true;
            this.txtDulieu.Name = "txtDulieu";
            this.txtDulieu.Size = new System.Drawing.Size(553, 29);
            this.txtDulieu.TabIndex = 0;
            this.txtDulieu.TextChanged += new System.EventHandler(this.txtDulieu_TextChanged);
            // 
            // btStart
            // 
            this.btStart.Location = new System.Drawing.Point(35, 444);
            this.btStart.Name = "btStart";
            this.btStart.Size = new System.Drawing.Size(120, 45);
            this.btStart.TabIndex = 1;
            this.btStart.Text = "LED1";
            this.btStart.UseVisualStyleBackColor = true;
            this.btStart.Click += new System.EventHandler(this.btLed1_Click);
            // 
            // btCompact
            // 
            this.btCompact.Location = new System.Drawing.Point(250, 444);
            this.btCompact.Name = "btCompact";
            this.btCompact.Size = new System.Drawing.Size(120, 45);
            this.btCompact.TabIndex = 1;
            this.btCompact.Text = "LED2";
            this.btCompact.UseVisualStyleBackColor = true;
            this.btCompact.Click += new System.EventHandler(this.btLed2_Click);
            // 
            // btExit
            // 
            this.btExit.Location = new System.Drawing.Point(468, 444);
            this.btExit.Name = "btExit";
            this.btExit.Size = new System.Drawing.Size(120, 45);
            this.btExit.TabIndex = 1;
            this.btExit.Text = "LED3";
            this.btExit.UseVisualStyleBackColor = true;
            this.btExit.Click += new System.EventHandler(this.btLed3_Click);
            // 
            // zedGraphControl1
            // 
            this.zedGraphControl1.Location = new System.Drawing.Point(35, 146);
            this.zedGraphControl1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.zedGraphControl1.Name = "zedGraphControl1";
            this.zedGraphControl1.ScrollGrace = 0D;
            this.zedGraphControl1.ScrollMaxX = 0D;
            this.zedGraphControl1.ScrollMaxY = 0D;
            this.zedGraphControl1.ScrollMaxY2 = 0D;
            this.zedGraphControl1.ScrollMinX = 0D;
            this.zedGraphControl1.ScrollMinY = 0D;
            this.zedGraphControl1.ScrollMinY2 = 0D;
            this.zedGraphControl1.Size = new System.Drawing.Size(545, 279);
            this.zedGraphControl1.TabIndex = 2;
            // 
            // txtNumberData
            // 
            this.txtNumberData.Controls.Add(this.zedGraphControl1);
            this.txtNumberData.Controls.Add(this.btExit);
            this.txtNumberData.Controls.Add(this.btCompact);
            this.txtNumberData.Controls.Add(this.btStart);
            this.txtNumberData.Controls.Add(this.textBox1);
            this.txtNumberData.Controls.Add(this.txtDulieu);
            this.txtNumberData.Location = new System.Drawing.Point(367, 12);
            this.txtNumberData.Name = "txtNumberData";
            this.txtNumberData.Size = new System.Drawing.Size(619, 514);
            this.txtNumberData.TabIndex = 2;
            this.txtNumberData.TabStop = false;
            this.txtNumberData.Text = "Dữ liệu";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(35, 90);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(553, 29);
            this.textBox1.TabIndex = 0;
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1011, 538);
            this.Controls.Add(this.txtNumberData);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "Giao tiếp máy tinh";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.txtNumberData.ResumeLayout(false);
            this.txtNumberData.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button btThoat;
        private System.Windows.Forms.Button btNgat;
        private System.Windows.Forms.Button btXoa;
        private System.Windows.Forms.Button btKetnoi;
        private System.Windows.Forms.ComboBox cbStop;
        private System.Windows.Forms.ComboBox cbParity;
        private System.Windows.Forms.ComboBox cbData;
        private System.Windows.Forms.ComboBox cbBaud;
        private System.Windows.Forms.ComboBox cbCom;
        private System.Windows.Forms.TextBox txtDulieu;
        private System.Windows.Forms.Button btStart;
        private System.Windows.Forms.Button btCompact;
        private System.Windows.Forms.Button btExit;
        private ZedGraph.ZedGraphControl zedGraphControl1;
        private System.Windows.Forms.GroupBox txtNumberData;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.TextBox textBox1;
        private System.IO.Ports.SerialPort serialPort1;
    }
}

