using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;
using System.Xml;
using ZedGraph;

namespace VS_Giao_tiep_may_tinh
{
    public partial class Form1 : Form
    {
        SerialPort P = new SerialPort();
        int tickStart = 0;
        public Form1()
        {
            InitializeComponent();
            // cai dat thong so cho cong COM
            // cai dat port name
            string[] ports = SerialPort.GetPortNames();
            cbCom.Items.AddRange(ports);
            P.ReadTimeout = 1000;
            // cai dat Baudrate
            string[] Baudrate = { "1200", "2400", "4800", "9600", "19200", "38400", "57600", "115200" };
            cbBaud.Items.AddRange(Baudrate);
            // cai dat cho data bit
            string[] DataBits = { "6", "7", "8" };
            cbData.Items.AddRange(DataBits);
            // cai dat cho parity
            string[] Parity = { "None", "Odd", "Even" };
            cbParity.Items.AddRange(Parity);
            // cai dat stop bit
            string[] stopbit = { "1", "1.5", "2" };
            cbStop.Items.AddRange(stopbit);
        }

        private void cbCom_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (P.IsOpen)
            {
                P.Close(); // Neu dang mo Port thi phai dong lai
            }
            P.PortName = cbCom.SelectedItem.ToString(); // Gan PortName bang COM da chon
        }

        private void cbBaud_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (P.IsOpen)
            {
                P.Close();
            }
            P.BaudRate = Convert.ToInt32(cbBaud.Text);
        }

        private void cbData_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (P.IsOpen)
            {
                P.Close();
            }
            P.DataBits = Convert.ToInt32(cbData.Text);
        }

        private void cbParity_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (P.IsOpen)
            {
                P.Close();
            }
            switch (cbParity.SelectedItem.ToString())
            {
                case "Odd":
                    P.Parity = Parity.Odd; break;
                case "None":
                    P.Parity = Parity.None; break;
                case "Even":
                    P.Parity = Parity.Even; break;
            }
        }

        private void cbStop_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (P.IsOpen)
            {
                P.Close();
            }
            switch (cbStop.SelectedItem.ToString())
            {
                case "1":
                    P.StopBits = StopBits.One; break;
                case "1.5":
                    P.StopBits = StopBits.OnePointFive; break;
                case "2":
                    P.StopBits = StopBits.Two; break;
            }
        }
        // Ham nay duoc su kien nhan du lieu goi den. Muc dich de hien thi thoi  

        private void btKetnoi_Click(object sender, EventArgs e)
        {
            try
            {
                P.Open();
                btNgat.Enabled = true;
                btKetnoi.Enabled = false;
                groupBox1.Enabled = false;
            }
            catch (Exception ex)
            {
                MessageBox.Show("Khong ket noi duoc.", "Thu lai", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btNgat_Click(object sender, EventArgs e)
        {
            P.Close();
            btKetnoi.Enabled = true;
            btNgat.Enabled = false;
            groupBox1.Enabled = true;
        }

        private void btXoa_Click(object sender, EventArgs e)
        {
            txtDulieu.Text = "";
        }

        private void btThoat_Click(object sender, EventArgs e)
        {
            DialogResult kq = MessageBox.Show("Ban thuc su muon thoat", "Neko_chan", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            if (kq == DialogResult.Yes)
            {
                MessageBox.Show("Cam on ban da su dung chuong trinh", "Neko_chan");
                P.Close();
                this.Close();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // khi khởi động sẽ được chạy
            GraphPane myPane = zedGraphControl1.GraphPane; // Khai báo sửa dụng Graph loại GraphPane;
            // Các thông tin cho đồ thị của mình
            myPane.Title.Text = "Bieu do nhiet do";
            myPane.XAxis.Title.Text = "Thời gian ";
            myPane.YAxis.Title.Text = "Nhiet do";
            // Định nghĩa list để vẽ đồ thị. Để các bạn hiểu rõ cơ chế làm
            //việc ở đây khai báo 2 list điểm <=> 2 đường đồ thị
            RollingPointPairList list1 = new RollingPointPairList(1200);
            // Ở đây sử dụng list với 1200 điểm (có thể thêm nhiều liệu tại đây)
            RollingPointPairList list2 = new RollingPointPairList(1200);
            // dòng dưới là định nghĩa curve để vẽ.
            LineItem curve1 = myPane.AddCurve("đường 1", list1, Color.Red,
            SymbolType.None); // Color màu đỏ, đặc trưng cho đường 1
                              // SymbolType là kiểu biểu thị đồ thị : điểm, đường tròn, tamgiác....
            LineItem curve2 = myPane.AddCurve("đường 2", list2, Color.Blue,
            SymbolType.None); // Color màu Xanh, đặc trưng cho đường 2
                              // ví dụ khoảng cách là 50ms 1 lần
            timer1.Interval = 50;
            //timer1.Enabled = true; // Kích hoạt cho timer1
            //timer1.Start(); // Chạy Timer1
            // Định hiện thị cho trục thời gian (Trục X)
            myPane.XAxis.Scale.Min = 0; // Min = 0;
            myPane.XAxis.Scale.Max = 30; // Mã = 30;
            myPane.XAxis.Scale.MinorStep = 1; // Đơn vị chia nhỏ nhất 1
            myPane.XAxis.Scale.MajorStep = 5; // Đơn vị chia lớn 5
                                              // Gọi hàm xác định cỡ trục
            zedGraphControl1.AxisChange();
            // Khởi động timer về vị trí ban đầu
            tickStart = Environment.TickCount;
            // ket noi cong com
            P.Encoding = Encoding.GetEncoding(28591);
            cbCom.SelectedIndex = 0;
            cbBaud.SelectedIndex = 3; // 9600 
            cbData.SelectedIndex = 2; // 8 
            cbParity.SelectedIndex = 0; // None 
            cbStop.SelectedIndex = 0; // None 
        }
        // ham phuc vu viec ve do thi
        public void draw(double setpoint1, double setpoint2)
        {
            if (zedGraphControl1.GraphPane.CurveList.Count <= 0)
                return;
            // Kiểm tra việc khởi tạo các đường curve
            // Đưa về điểm xuất phát
            LineItem curve1 = zedGraphControl1.GraphPane.CurveList[0] as LineItem;
            LineItem curve2 = zedGraphControl1.GraphPane.CurveList[1] as LineItem;
            if (curve1 == null)
                return;
            if (curve2 == null)
                return;
            // list chứa các điểm.
            // Get the PointPairList
            IPointListEdit list1 = curve1.Points as IPointListEdit;
            IPointListEdit list2 = curve2.Points as IPointListEdit;
            if (list1 == null)
                return;
            if (list2 == null)
                return;
            // Time được tính bằng ms
            double time = (Environment.TickCount - tickStart) / 1000.0;
            // Tính toán giá trị hiện thị
            // Muốn hiện thị cái gì thì chỉ việc thay vào setpointx
            list1.Add(time, setpoint1); // Đây chính là hàm hiển thị dữ liệu của mình lên đồ thị
            // list2.Add(time, setpoint2); // Đây chính là hàm hiển thị dữ
            //liệu của mình lên đồ thị
            // Ko vẽ setpoint2 mà thử vẽ đồ thị hình sin với 3 seconds percycle
            list2.Add(time, setpoint2); // Math.Sin(2.0 * Math.PI * time / 3.0)
            // đoạn chương trình thực hiện vẽ đồ thị
            Scale xScale = zedGraphControl1.GraphPane.XAxis.Scale;
            if (time > xScale.Max - xScale.MajorStep)
            {
                //xScale.Max = time + xScale.MajorStep;
                // xScale.Min = xScale.Max - 30.0; // Timer chạy qua 30 sẽ tự
                //động dịch chuyển tịnh tiến sang trái
                // Nếu ko muốn dịch chuyển mà chạy bắt đầu từ 0 thì :
                xScale.Min = 0;
                if (btCompact.Text == "COMPACT")
                {
                    xScale.Max = time + xScale.MajorStep;
                    xScale.Min = xScale.Max - 30.0;
                }
                else
                {
                    xScale.Max = time + xScale.MajorStep;
                    xScale.Min = 0;
                }
            }
            // Vẽ đồ thị
            zedGraphControl1.AxisChange();
            // Force a redraw
            zedGraphControl1.Invalidate();
        }
        
        private void btLed1_Click(object sender, EventArgs e)
        {
            if(P.IsOpen == true)
            {
                P.Write("1");
            }
            else
            {
                MessageBox.Show("chưa mở cổng COM");
            }
        }

        private void btLed2_Click(object sender, EventArgs e)
        {
            if (P.IsOpen == true)
            {
                P.Write("2");
            }
            else
            {
                MessageBox.Show("chưa mở cổng COM");
            }
        }

        private void btLed3_Click(object sender, EventArgs e)
        {
            if (P.IsOpen == true)
            {
                P.Write("3");
            }
            else
            {
                MessageBox.Show("chưa mở cổng COM");
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            draw(5,2);
        }
        Action<string> serialPortReceiverAction;
        
        // ham xu ly du lieu nhan ve
        private void serialPortReceiver(string input)
        {
            txtDulieu.Text = txtDulieu.Text + input;
            char[] chrs = input.ToCharArray();
            foreach (char c in chrs)
            {
                txtNumberData.Text += ((int) c).ToString() + ", ";
            }
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            serialPortReceiverAction = serialPortReceiver;
            try
            {
                this.BeginInvoke(serialPortReceiverAction, P.ReadExisting());
            }
            catch { }
        }

        private void txtDulieu_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
