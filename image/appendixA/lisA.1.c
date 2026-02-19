
#include <Stdlib.h>
#include <String.h>
#include <math.h>
#include <Psim.h>

// PLACE GLOBAL VARIABLES OR USER FUNCTIONS HERE...


/*************************************************状態量の定義****************************************************/
static double Vs_u = 0.0, Vs_v = 0.0, Vs_w = 0.0;//系統電圧U，V,Wの相電圧の定義
static double Vs_uv = 0.0, Vs_vw = 0.0, Vs_wu = 0.0;//系統電圧U，V,Wの相電圧の定義
static double Vc_u = 0.0, Vc_v = 0.0, Vc_w = 0.0;//キャパシタ電圧U，V,Wの相電圧の定義
static double Ic_u = 0.0, Ic_v = 0.0, Ic_w = 0.0;//U,V,W相の出力電流の定義
static double IL1_u = 0.0, IL1_v = 0.0, IL1_w = 0.0;//U,V,W相のフィルタインダクタ電流の定義
static double Io_u = 0.0, Io_v = 0.0, Io_w = 0.0;//U,V,W相の出力電流の定義

/*************************************************演算用変数の定義****************************************************/
static double Vs_a = 0.0, Vs_b = 0.0;//系統電圧a,bの相電圧の定義
static double Vc_a = 0.0, Vc_b = 0.0;//系統電圧a,bの相電圧の定義
static double Ic_a = 0.0, Ic_b = 0.0;//出力電流a,bの定義
static double IL1_a = 0.0, IL1_b = 0.0;//フィルタインダクタ電流a,bの定義

static double Vs_d = 0.0, Vs_q = 0.0;//dq変換後の系統電圧の相電圧の定義
static double Vs_d_k_1 = 0.0, Vs_q_k_1 = 0.0;//一次点前のdq変換後の系統電圧の相電圧の定義
static double Vc_d = 0.0, Vc_q = 0.0;//dq変換後の系統電圧の相電圧の定義
static double Ic_d = 0.0, Ic_q = 0.0;//dq変換後の出力電流の定義
static double IL1_d = 0.0, IL1_q = 0.0;//dq変換後のフィルタインダクタ電流の定義

static double Io_ref_d_h = 0.0,Io_ref_q_h = 0.0;
static double Io_ref_u_h = 0.0,Io_ref_v_h = 0.0,Io_ref_w_h = 0.0;
static double Io_ref_a_h = 0.0,Io_ref_b_h = 0.0;

static double Io_d_ref = 0.0, Io_q_ref = 0.0;//dq軸の出力電流指令値の定義        
static double Vs_d_ref = 0.0, Vs_q_ref = 0.0;//dq軸の系統電圧指令値の定義
static double Io_ref_amp = 0.0;

static double IL1_a_ref_dev = 0.0,IL1_b_ref_dev = 0.0;//abの出力電流指令値の定義        
static double IL1_u_ref_dev = 0.0,IL1_v_ref_dev = 0.0,IL1_w_ref_dev = 0.0;//abの出力電流指令値の定義        

static double IL1_a_ref = 0.0,IL1_b_ref = 0.0;//abの出力電流指令値の定義        
static double IL1_u_ref = 0.0,IL1_v_ref = 0.0,IL1_w_ref = 0.0;//abの出力電流指令値の定義        

static double Vc_a_ref = 0.0,Vc_b_ref = 0.0;//abのキャパシタ電圧指令値の定義
static double Vc_u_ref = 0.0,Vc_v_ref = 0.0,Vc_w_ref = 0.0;//uvwキャパシタ指令値の定義

static double Vs_d_nom = 0.0, Vs_q_nom = 0.0;//dq軸の系統電圧指令値(固定値)の定義

static double Error_ACR1_d = 0.0,Error_ACR1_q = 0.0;//出力電流と出力電流指令値の偏差
static double Int_ACR1_d = 0.0,Int_ACR1_q;//出力電流の積分バッファ
static double u_ACR1_d = 0.0,u_ACR1_q;//出力電流の操作量

static double Error_ACR2_d = 0.0,Error_ACR2_q = 0.0;//インダクタ電流とインダクタ電流指令値の偏差
static double Int_ACR2_d = 0.0,Int_ACR2_q;//インダクタ電流の積分バッファ
static double u_ACR2_d = 0.0,u_ACR2_q;//インダクタ電流の操作量

static double u_ACR_d = 0.0,u_ACR_q = 0.0;//ACRの最終的な操作量

static double soft_start_gain = 0.0;//soft start gain
static double Vs_d_ref_soft_start = 0.0,Vs_q_ref_soft_start = 0.0;//soft start　gain乗算後の系統指令値

static double Error_AVR_d = 0.0,Error_AVR_q = 0.0;//系統電圧指令値とキャパシタ電圧の偏差
static double Int_AVR_d = 0.0,Int_AVR_q;//インダクタ電流の積分バッファ
static double u_AVR_d = 0.0,u_AVR_q;//インダクタ電流の操作量

static double u_d = 0.0,u_q = 0.0;//最終的な操作量　ACR or AVR
static double u_a = 0.0,u_b = 0.0;//操作量の逆dq変換
static double u_u = 0.0,u_v = 0.0,u_w = 0.0;//操作量の二相三相変換
static double u_MS_u = 0.0,u_MS_v = 0.0,u_MS_w = 0.0;//操作量の二相三相変換

//Edc抜き確認用

static double u_a_ACR_AVR = 0.0,u_b_ACR_AVR = 0.0;//操作量の逆dq変換
static double u_u_ACR_AVR = 0.0,u_v_ACR_AVR = 0.0,u_w_ACR_AVR = 0.0;//操作量の二相三相変換

/*************************************************PLLの定義****************************************************/ 
static double VCO = 0.0;//電圧制御発振器 Voltage Controlled Oscillator
static double Error_PLL = 0.0;//偏差の定義
static double Int_PLL = 0.0;//積分bufferの定義
static double Kp_PLL = 0.0,Ki_PLL = 0.0;//PLLの比例ゲイン，積分ゲイン
static double u_PLL = 0.0;//PLLの操作量
static double f_u = 0.0;//操作量と基本周波数の和
static double dth = 0.0;//サンプリング周波数当たりにおけるキャリア周期あたりに増加する角度

/*************************************************パラメータの定義****************************************************/    

static double f = 0.0;//基本周波数
static double fs = 0.0;//サンプリング周波数
static double fc = 0.0;//キャリア周波数
static double Ts = 0.0;//サンプリング周期
static double Tc = 0.0;//キャリア周期
static double omega = 0.0;//角速度
static double Edc = 0.0;//電源電圧
static double C = 0.0;
static double C_arm = 0.0;
static double L1 = 0.0;
static double Kp_ACR2 = 0.0;
static double Ki_ACR2 = 0.0;
static double Kp_AVR = 0.0;
static double Ki_AVR = 0.0;
static double Vs_mode = 0.0;//現在未使用
static double ACR_mode = 0.0;//現在未使用
static double ACR_AVR_mode = 0.0;//現在未使用
static double PI = 0.0;
static double Idis_a = 0.0;
static double Idis_b = 0.0;
static double Io_a = 0.0;
static double Io_b = 0.0;
static double z11 = 0.0;
static double z12 = 0.0;
static double z13 = 0.0;
static double z14 = 0.0;
static double zg1 = 0.0;
static double Tri = 0.0;
static double Tri_k_1 = 0.0;
static double hold_flag_1 = 0.0;
static double hold_flag_2 = 0.0;



/////////////////////////////////////////////////////////////////////
// FUNCTION: SimulationStep
//   This function runs at every time step.
//double t: (read only) time
//double delt: (read only) time step as in Simulation control
//double *in: (read only) zero based array of input values. in[0] is the first node, in[1] second input...
//double *out: (write only) zero based array of output values. out[0] is the first node, out[1] second output...
//int *pnError: (write only)  assign  *pnError = 1;  if there is an error and set the error message in szErrorMsg
//    strcpy(szErrorMsg, "Error message here..."); 
// DO NOT CHANGE THE NAME OR PARAMETERS OF THIS FUNCTION
void SimulationStep(
		double t, double delt, double *in, double *out,
		 int *pnError, char * szErrorMsg,
		 void ** reserved_UserData, int reserved_ThreadIndex, void * reserved_AppPtr)
{
// ENTER YOUR CODE HERE...
	Ic_u		= in[0];
	Ic_v		= in[1];
	Ic_w		= in[2];
	IL1_u		= in[3];
	IL1_v		= in[4];
	IL1_w		= in[5];
	Vc_u		= in[6];
	Vc_v		= in[7];
	Vc_w		= in[8];
	Vs_u		= in[9];
	Vs_v		= in[10];
	Vs_w		= in[11];
	f			= in[12];
	fs			= in[13];
	fc			= in[14];
	Ts			= in[15];
	Tc			= in[16];
	Kp_PLL		= in[17];
	Ki_PLL		= in[18];
	C_arm		= in[19];
	L1		= in[20];
	VCO		= in[21];
	Io_u		= in[22];
	Io_v		= in[23];
	Io_w		= in[24];
	Vs_d_nom	= in[25];
	Vs_q_nom	= in[26];
	Edc		= in[27];
	Io_d_ref	= in[28];
	Io_q_ref	= in[29];
	Io_ref_amp	= in[30];
	PI					= in[31];
	Tri = in[32];


	C = 3*C_arm;
	Vs_uv = Vs_u - Vs_v;
	Vs_vw = Vs_v - Vs_w;
	Vs_wu = Vs_w - Vs_u;
	IL1_u_ref = Io_ref_amp * sin(VCO);
	IL1_v_ref = Io_ref_amp * sin(VCO - (2.0 * PI / 3.0));
	IL1_w_ref = Io_ref_amp * sin(VCO - (4.0 * PI / 3.0));
	IL1_u_ref_dev= Io_ref_amp * sin(VCO+(PI/36));
	IL1_v_ref_dev = Io_ref_amp * sin(VCO - (2.0 * PI / 3.0)+(PI/36));
	IL1_w_ref_dev = Io_ref_amp * sin(VCO - (4.0 * PI / 3.0)+(PI/36));


/************************************************ab変換*****************************************************************/

	Vs_a = (2.0/3.0)*(Vs_u - (1.0/2.0)*Vs_v - (1.0/2.0)*Vs_w);
	Vs_b = (2.0/3.0)*(sqrt(3.0)/2.0*Vs_v - sqrt(3.0)/2.0*Vs_w);

//	Vs_a = (2.0 / 3.0)*((sqrt(3.0) / 2.0) * (Vs_wu));
//	Vs_b = (2.0 / 3.0)*(((1.0 / 2.0) * (Vs_uv)) - ((1.0 / 2.0) * (Vs_vw)));

	Vc_a = (2.0 / 3.0)*(((1.0 / 2.0) * (Vc_u)) - ((1.0 / 2.0) * (Vc_w)));
	Vc_b = (2.0 / 3.0)*((sqrt(3.0) / 2.0) * (Vc_v));


//	Vc_a = (2.0/3.0)*(-sqrt(3.0)/2.0*Vc_v + sqrt(3.0)/2.0*Vc_w);
//	Vc_b = (2.0/3.0)*(Vc_u - (1.0/2.0)*Vc_v - (1.0/2.0)*Vc_w);

	IL1_a = (2.0/3.0)*(IL1_u - (1.0/2.0)*IL1_v - (1.0/2.0)*IL1_w);
	IL1_b = (2.0/3.0)*(sqrt(3.0)/2.0*IL1_v - sqrt(3.0)/2.0*IL1_w);

	Ic_a = (2.0/3.0)*(Ic_u - (1.0/2.0)*Ic_v - (1.0/2.0)*Ic_w);
	Ic_b = (2.0/3.0)*(sqrt(3.0)/2.0*Ic_v - sqrt(3.0)/2.0*Ic_w);

//	Ic_a = (2.0 / 3.0)*((sqrt(3.0) / 2.0) * (Ic_w));
//	Ic_b = (2.0 / 3.0)*(((1.0 / 2.0) * (Ic_u)) - ((1.0 / 2.0) * (Ic_v)));

/*
	Vs_b = (2.0/3.0)*(-sqrt(3.0)/2.0*Vs_v + sqrt(3.0)/2.0*Vs_w);
	Vs_a = (2.0/3.0)*(Vs_u - (1.0/2.0)*Vs_v - (1.0/2.0)*Vs_w);

	Vc_b = (2.0/3.0)*(-sqrt(3.0)/2.0*Vc_v + sqrt(3.0)/2.0*Vc_w);
	Vc_a = (2.0/3.0)*(Vc_u - (1.0/2.0)*Vc_v - (1.0/2.0)*Vc_w);

	IL1_b = (2.0/3.0)*(-sqrt(3.0)/2.0*IL1_v + sqrt(3.0)/2.0*IL1_w);
	IL1_a = (2.0/3.0)*(IL1_u - (1.0/2.0)*IL1_v - (1.0/2.0)*IL1_w);

	Ic_b = (2.0/3.0)*(-sqrt(3.0)/2.0*Ic_v + sqrt(3.0)/2.0*Ic_w);
	Ic_a = (2.0/3.0)*(Ic_u - (1.0/2.0)*Ic_v - (1.0/2.0)*Ic_w);

/************************************************系統電圧のdq変換*****************************************************************/
	Vs_d_k_1 = Vs_a * sin(VCO) + Vs_b * cos(VCO);
	Vs_q_k_1 = Vs_a * cos(VCO) - Vs_b * sin(VCO);

/************************************************PLL*****************************************************************/
/*
	Error_PLL = Vs_q_k_1;
	Int_PLL = Int_PLL + Error_PLL*Ts;
	u_PLL = Kp_PLL*Error_PLL + Ki_PLL*Int_PLL;
	f_u = u_PLL + f;

	dth = 2*M_PI*f_u*Tc;

	if(VCO > 2*M_PI){
		VCO = 0;
	}else{
		VCO = VCO + dth;
	}	
*/
/************************************************dq変換*****************************************************************/

	Vs_d = Vs_a * sin(VCO) + Vs_b * cos(VCO);
	Vs_q = Vs_a * cos(VCO) - Vs_b * sin(VCO);

	Vc_d = sin(VCO)*Vc_a + cos(VCO)*Vc_b;
	Vc_q = cos(VCO)*Vc_a - sin(VCO)*Vc_b;

	IL1_d = sin(VCO)*IL1_a + cos(VCO)*IL1_b;
	IL1_q = cos(VCO)*IL1_a - sin(VCO)*IL1_b;

	Ic_d = sin(VCO)*Ic_a + cos(VCO)*Ic_b;
	Ic_q = cos(VCO)*Ic_a - sin(VCO)*Ic_b;

/*************************************************電流指令値生成****************************************************/

	IL1_a_ref	=	(2.0/3.0)*(IL1_u_ref - (1.0/2.0)*IL1_v_ref - (1.0/2.0)*IL1_w_ref);
	IL1_b_ref	=	(2.0/3.0)*(sqrt(3.0)/2.0*IL1_v_ref - sqrt(3.0)/2.0*IL1_w_ref);

	IL1_a_ref_dev	=	(2.0/3.0)*(IL1_u_ref_dev - (1.0/2.0)*IL1_v_ref_dev - (1.0/2.0)*IL1_w_ref_dev);
	IL1_b_ref_dev	=	(2.0/3.0)*(sqrt(3.0)/2.0*IL1_v_ref_dev - sqrt(3.0)/2.0*IL1_w_ref_dev);


	Idis_a = IL1_a_ref - IL1_a;
	Idis_b = IL1_b_ref - IL1_b;
/*
	Idis_a = IL1_a_ref_dev - IL1_a;
	Idis_b = IL1_b_ref_dev - IL1_b;
*/
	Io_a = IL1_a - Ic_a +  Idis_a;
	Io_b = IL1_b - Ic_b +  Idis_b;

//	Io_a = (2.0/3.0)*(Io_u - (1.0/2.0)*Io_v - (1.0/2.0)*Io_w);
//	Io_b = (2.0/3.0)*(sqrt(3.0)/2.0*Io_v - sqrt(3.0)/2.0*Io_w);

/************************************************SRDBDC*****************************************************************/
//DC-SRDB制御を使用する際は下記のコメントを解除する
	z11 = cosh(Ts/sqrt(L1*C));
	z12 = -(sqrt(C)*sinh(Ts/sqrt(L1*C)))/sqrt(L1);
	z13 = 1 - cosh(Ts/sqrt(L1*C));
	z14 = cosh(Ts/sqrt(L1*C)) - 1;
	zg1 = ((Edc/2*cosh(Ts/sqrt(L1*C)))/L1)*1;

//DC-MSSRDB制御を使用する際は下記のコメントを解除する
	z11 = cosh(Ts/sqrt(L1*C));
	z12 = -(sqrt(C)*sinh(Ts/sqrt(L1*C)))/sqrt(L1);
	z13 = 1 - cosh(Ts/sqrt(L1*C));
	z14 = cosh(Ts/sqrt(L1*C)) - 1;
	zg1 = ((Edc/2*cosh(Ts/sqrt(L1*C)))/L1)*1;


	u_a = (IL1_a_ref - (z11*IL1_a) - (z12*Vc_a) - (z13*Io_a) - (z14*Idis_a))/zg1;
	u_b = (IL1_b_ref - (z11*IL1_b) - (z12*Vc_b) - (z13*Io_b) - (z14*Idis_b))/zg1;
/*
	u_a = (IL1_a_ref_dev - (z11*IL1_a) - (z12*Vc_a) - (z13*Io_a) - (z14*Idis_a))/zg1;
	u_b = (IL1_b_ref_dev - (z11*IL1_b) - (z12*Vc_b) - (z13*Io_b) - (z14*Idis_b))/zg1;
*/
/************************************************2相3相変換*****************************************************************/

	//u_a = sin(VCO)*u_d + cos(VCO)*u_q;
	//u_b = cos(VCO)*u_d - sin(VCO)*u_q;

//DC-MSSRDB制御を使用する際は下記のコメントを解除する
	u_MS_u = u_a;
	u_MS_v = (-(1.0/2.0)*u_a + (sqrt(3.0)/2.0)*u_b);
	u_MS_w = (-(1.0/2.0)*u_a - (sqrt(3.0)/2.0)*u_b);

//DC-SRDB制御を使用する際は下記のコメントを解除する
	u_u = u_a;
	u_v = (-(1.0/2.0)*u_a + (sqrt(3.0)/2.0)*u_b);
	u_w = (-(1.0/2.0)*u_a - (sqrt(3.0)/2.0)*u_b);


/*
	u_u = (3/2)*(u_a - 1/sqrt(3)*u_b);
	u_v = (3/2)*((2.0/sqrt(3.0))*u_b);
	u_w = (3/2)*(-u_a - 1/sqrt(3)*u_b);
*/
	IL1_u_ref = IL1_a_ref;
	IL1_v_ref =  -(1.0/2.0)*IL1_a_ref + (sqrt(3.0)/2.0)*IL1_b_ref;
	IL1_w_ref =  -(1.0/2.0)*IL1_a_ref - (sqrt(3.0)/2.0)*IL1_b_ref;

	Vs_u = Vs_a;
	Vs_v = (-(1.0/2.0)*Vs_a + (sqrt(3.0)/2.0)*Vs_b);
	Vs_w = -(1.0/2.0)*Vs_a - (sqrt(3.0)/2.0)*Vs_b;

	Vc_u = Vc_a;
	Vc_v = (-(1.0/2.0)*Vc_a + (sqrt(3.0)/2.0)*Vc_b);
	Vc_w = -(1.0/2.0)*Vc_a - (sqrt(3.0)/2.0)*Vc_b;
	


/*
	u_u = (3.0/2.0)*u_b;
	u_v = (3.0/2.0)*(-(sqrt(3.0)/2.0)*u_a - (1.0/2.0)*u_b);
	u_w = (3.0/2.0)*((sqrt(3.0)/2.0)*u_a - (1.0/2.0)*u_b);

	IL1_u_ref =(3.0/2.0)* IL1_b_ref;
	IL1_v_ref = (3.0/2.0)*(-(sqrt(3.0)/2.0)*IL1_a_ref - (1.0/2.0)*IL1_b_ref);
	IL1_w_ref = (3.0/2.0)*((sqrt:(3.0)/2.0)*IL1_a_ref - (1.0/2.0)*IL1_b_ref);

/*

	u_u = u_a;
	u_v = (sqrt(3.0)/2.0)*u_b - (1.0/2.0)*u_a;
	u_w = -(sqrt(3.0)/2.0)*u_b - (1.0/2.0)*u_a;

/*************************************************出力ポートの定義****************************************************/
	
//SRDB制御を使用する際は//startから//endまでをコメントアウトする

//start
/*
	if(Tri_k_1>Tri){
		if((Tri > u_MS_u||Tri > u_MS_v||Tri > u_MS_w)&&hold_flag_1==0){
			u_u = u_MS_u;
			u_v = u_MS_v;
			u_w = u_MS_w;
			hold_flag_2=0;
		}if(Tri < u_MS_u||Tri < u_MS_v||Tri < u_MS_w){
			u_u = u_u;
			u_v = u_v;
			u_w = u_w;
			hold_flag_1=1;
		}

	}else if(Tri_k_1<Tri){
		if((Tri < u_MS_u||Tri < u_MS_v||Tri < u_MS_w)&&hold_flag_2==0){
			u_u = u_MS_u;
			u_v = u_MS_v;
			u_w = u_MS_w;
			hold_flag_1=0;
		}if(Tri > u_MS_u||Tri > u_MS_v||Tri > u_MS_w){
			u_u = u_u;
			u_v = u_v;
			u_w = u_w;
			hold_flag_2=1;
		}
	}
*/
//end

	Tri_k_1 = Tri;



		out[0]	= u_u;
		out[1]	= u_v;
		out[2]	= u_w;
		out[3]	= u_a;
		out[4]  = u_b;
		out[5]  = u_d;
		out[6]  = u_q;
		out[7]  = VCO;
		out[8]  = soft_start_gain;
		out[9]  = IL1_a_ref;
		out[10] = IL1_b_ref;
		out[11] = IL1_a;
		out[12] = IL1_b;
		out[13] = Io_ref_v_h;
		out[14] = Io_ref_w_h;
		out[15] = Vs_a;
		out[16] = Vs_b;
		out[17] = Vc_a;
		out[18] = Vc_b;
		out[19] = Io_a;
		out[20] = Io_b;
		out[21] = IL1_u_ref;
		out[22] = IL1_v_ref;
		out[23] = IL1_w_ref;
		out[24] = Idis_a;
		out[25] = Idis_b;
		out[26] = Vs_u;
		out[27] = Vs_v;
		out[28] = Vs_w;
		out[29] = Vc_u;
		out[30] = Vc_v;
		out[31] = Vc_w;     
		out[32] = Error_ACR1_q = Io_q_ref - IL1_q;
		out[33] = z11;
		out[34] = z12;
		out[35] = z13;
		out[36] = z14;
		out[37] = zg1;
		out[38]=hold_flag_1;
		out[39]=hold_flag_2;
		out[40]  = IL1_a_ref;
		out[41] = IL1_b_ref;
		out[42] = IL1_u_ref;
		out[43] = IL1_v_ref;
		out[44] = IL1_w_ref;


}


/////////////////////////////////////////////////////////////////////
// FUNCTION: SimulationBegin
//   Initialization function. This function runs once at the beginning of simulation
//   For parameter sweep or AC sweep simulation, this function runs at the beginning of each simulation cycle.
//   Use this function to initialize static or global variables.
//const char *szId: (read only) Name of the C-block 
//int nInputCount: (read only) Number of input nodes
//int nOutputCount: (read only) Number of output nodes
//int nParameterCount: (read only) Number of parameters is always zero for C-Blocks.  Ignore nParameterCount and pszParameters
//int *pnError: (write only)  assign  *pnError = 1;  if there is an error and set the error message in szErrorMsg
//    strcpy(szErrorMsg, "Error message here..."); 
// DO NOT CHANGE THE NAME OR PARAMETERS OF THIS FUNCTION
void SimulationBegin(
		const char *szId, int nInputCount, int nOutputCount,
		 int nParameterCount, const char ** pszParameters,
		 int *pnError, char * szErrorMsg,
		 void ** reserved_UserData, int reserved_ThreadIndex, void * reserved_AppPtr)
{
// ENTER INITIALIZATION CODE HERE...
  
}


/////////////////////////////////////////////////////////////////////
// FUNCTION: SimulationEnd
//   Termination function. This function runs once at the end of simulation
//   For parameter sweep or AC sweep simulation, this function runs at the end of each simulation cycle.
//   Use this function to de-allocate any allocated memory or to save the result of simulation in an alternate file.
// Ignore all parameters for C-block 
// DO NOT CHANGE THE NAME OR PARAMETERS OF THIS FUNCTION
void SimulationEnd(const char *szId, void ** reserved_UserData, int reserved_ThreadIndex, void * reserved_AppPtr)
{




}


