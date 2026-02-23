
#include <Stdlib.h>
#include <String.h>
#include <math.h>
#include <Psim.h>

// PLACE GLOBAL VARIABLES OR USER FUNCTIONS HERE...
static double Vs_u = 0.0, Vs_v = 0.0, Vs_w = 0.0, Vs_a = 0.0, Vs_b = 0.0, Vs_a2 = 0.0, Vs_b2 = 0.0, Vs_0 = 0.0, Vs_uv = 0.0, Vs_vw = 0.0, Vs_wu = 0.0;
static double Vs_aa = 0.0, Vs_bb = 0.0, Vs_00 = 0.0;
static double dtVs_a = 0.0, dtVs_b = 0.0, dtVs_0 = 0.0;
static double Vc_u = 0.0, Vc_v = 0.0, Vc_w = 0.0, Vc_a = 0.0, Vc_b = 0.0, Vc_0 = 0.0, Vc_uv = 0.0, Vc_vw = 0.0, Vc_wu = 0.0;
static double Io_u = 0.0, Io_v = 0.0, Io_w = 0.0, Io_a = 0.0, Io_b = 0.0, Io_0 = 0.0;
static double IL1_u = 0.0, IL1_v = 0.0, IL1_w = 0.0, IL1_a = 0.0, IL1_b = 0.0, IL1_0 = 0.0;
static double Vs_d = 0.0, Vs_q = 350.0;
static double Vinv_uv = 0.0, Vinv_vw = 0.0, Vinv_wu = 0.0;
static double Ioref_u = 0.0, Ioref_v = 0.0, Ioref_w = 0.0, Ioref_a = 0.0, Ioref_b = 0.0, Ioref_0 = 0.0;
static double Ioref_u_samp = 0.0, Ioref_v_samp = 0.0, Ioref_w_samp = 0.0;
static double Vcref_u = 0.0, Vcref_v = 0.0, Vcref_w = 0.0;
static double Vcref_a = 0.0, Vcref_b = 0.0, Vcref_0 = 0.0;
static double delta_Ta = 0.0, delta_Tb = 0.0, delta_T0 = 0.0;
static double Vcref_a_open, Vcref_b_open;
static double Vs_u1 = 0.0,Vs_u2 = 0.0,Vs_u3 = 0.0, Vs_v1 = 0.0, Vs_w1 = 0.0;
double f = 0.0, Tc = 0.0, dth = 0.0, PI = 0.0, omega = 0.0, Ts = 0.0, Ts_dq = 0.0, t1 = 0.0, t2 = 0.0;
static double delta_u = 0.0, delta_v = 0.0, delta_w = 0.0;
static double L1, C, C_Y, C_samp, L2, Edc, fs;
static double pTc = 0.0, pte = 0.0;
static double vco = 0.0, vco2 = 0.0;
static double flg = 1.0;
static double E = 0.0, Int = 0.0, u = 0.0, KP = 0.0, KI = 0.0;
static double f1 = 50.0;
static double tri_h = 0.0, tri_h_k1 = 0.0, tri_l = 0.0, tri_l_k1 = 0.0, hold_u = 0.0, hold_v = 0.0, hold_w = 0.0, cnt = -1.0;
static double dVs_u, Vs_u_k1 = 0.0, dVs_v, Vs_v_k1 = 0.0, dVs_w, Vs_w_k1 = 0.0;
int mode_u = 0, mode_v = 0, mode_w = 0, control_mode = 0.0;
int OC = 1;
int OC_flag;
//int cnt_OC_flag;
int cnt_OC = 0;

static double E_u = 0.0, Int_u = 0.0, u_u = 0.0;
static double E_v = 0.0, Int_v = 0.0, u_v = 0.0;
static double E_w = 0.0, Int_w = 0.0, u_w = 0.0;
static double f1_u = 50.0, f1_v = 50.0, f1_w = 50.0;
static double vco_u = 0.0, vco_v = -2.0*3.14159265 / 3.0, vco_w = -4.0*3.14159265 / 3.0;
static double Vre_u[19], Vim_u[19], Vs_u_d[19], Vs_u_q[19];
static double Vre_v[9], Vim_v[9], Vs_v_d[9], Vs_v_q[9];
static double Vre_w[9], Vim_w[9], Vs_w_d[9], Vs_w_q[9];
static double k_u[17], k_v[9], k_w[3],k_u_ave[3];
static double dth_u = 0.0, dth_v = 0.0, dth_w = 0.0;
static double VCO = 0.0;
static double Io_ref_amp  = 0.0;

static double IL1_a_ref_dev = 0.0,IL1_b_ref_dev = 0.0;//abの出力電流指令値の定義        
static double IL1_u_ref_dev = 0.0,IL1_v_ref_dev = 0.0,IL1_w_ref_dev = 0.0;//abの出力電流指令値の定義        

static double IL1_a_ref = 0.0,IL1_b_ref = 0.0;//abの出力電流指令値の定義        
static double IL1_u_ref = 0.0,IL1_v_ref = 0.0,IL1_w_ref = 0.0;//abの出力電流指令値の定義      

static double Idis_a = 0.0;
static double Idis_b = 0.0;
static double z11 = 0.0;
static double z12 = 0.0;
static double z13 = 0.0;
static double z14 = 0.0;
static double zg1 = 0.0;

static double Ic_u = 0.0, Ic_v = 0.0, Ic_w = 0.0;//U,V,W相の出力電流の定義
static double Ic_a = 0.0, Ic_b = 0.0;//出力電流a,bの定義

static double Vs_d_nom = 0.0, Vs_q_nom = 0.0;//dq軸の系統電圧指令値(固定値)の定義
static double PLL_1k_cnt = 100.0;//1kHzPLLのカウント用
static double KP_q = 0.00,KI_q = 0.00;//疑似dqPLLgain

static double count_Ts2 = 0,count_Ts3 = 0;
static double a = 0,LPF_V = 0,Vre_u_buf = 0;
static double Vs_k_u_diff[19],Vs_k_v_diff[9],Vs_k_w_diff[9];
static double Vs_u_d_ave = 0,Vs_u_q_ave = 0,Vs_v_d_ave = 0,Vs_v_q_ave = 0,Vs_w_d_ave = 0,Vs_w_q_ave = 0;
static double Vre_u_ave = 0,Vim_u_ave = 0,Vre_v_ave = 0,Vim_v_ave = 0,Vre_w_ave = 0,Vim_w_ave = 0;
static double Vs_u_d_ave_new[2];
static double Vs_u_q_ave_new[2];

// ===== Sampling Times =====
static double Ts_10M    = 1.0 / 10000000.0;   // 10 MHz
static double Ts_1M    = 1.0 / 1000000.0;   // 10 MHz
static double Ts_20k   = 1.0 /  20000.0;    // 20 kHz
static double Ts_17k    = 1.0 /   17000.0;    //17 kHz
static double Ts_15k   = 1.0 /  15000.0;    // 15 kHz
static double Ts_14k    = 1.0 /   14000.0;    // 14 kHz
static double Ts_13k    = 1.0 /   13000.0;    // 13 kHz
static double Ts_12k   = 1.0 /  12000.0;   //12 kHz
static double Ts_11k    = 1.0 /  11000.0;    // 11 kHz
static double Ts_10k   = 1.0 /  10000.0;    // 10 kHz 
static double Ts_9k   = 1.0 /  9000.0;    // 9 kHz 
static double Ts_8k   = 1.0 /  8000.0;    // 8 kHz 
static double Ts_7k    = 1.0 /   7000.0;    // 7 kHz
static double Ts_6k7   = 1.0 /   6700.0;    // 6.7 kHz
static double Ts_5k    = 1.0 /   5000.0;    // 5 kHz
static double Ts_4k    = 1.0 /   4000.0;    // 5 kHz
static double Ts_3k8    = 1.0 /   3800.0;    // 3.8 kHz
static double Ts_3k4    = 1.0 /   3400.0;    // 3.4 kHz
static double Ts_3k    = 1.0 /  3000.0;    // 3 kHz
static double Ts_2k    = 1.0 /  2000.0;    // 2 kHz
static double Ts_1k    = 1.0 /  1000.0;    // 1 kHz
static double Ts_0k85    = 1.0 /   850.0;    // 0.85 kHz

//----------------------------------


static double Ts_500k  = 1.0 / 500000.0;    // 500 kHz
static double Ts_250k  = 1.0 / 250000.0;    // 250 kHz
static double Ts_125k  = 1.0 / 125000.0;    // 125 kHz
static double Ts_62k   = 1.0 /  62000.0;    // 62 kHz 



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

	Vs_u = in[0];
	Vs_v = in[1];
	Vs_w = in[2];
	Vc_u = in[3];
	Vc_v = in[4];
	Io_u = in[6];
	Io_v = in[7];
	IL1_u = in[9];
	IL1_v = in[10];
	Ts = in[12];//こいつ
	//vco = in[13];
	//Edc = in[14] / 4;
	Edc = in[14] / 2;
	L1 = in[15];
	C_samp = in[16];
	L2 = in[17];
	//C = 3.0 * C_samp;
	C= C_samp;
	tri_h = in[18];
	tri_l = in[19];
	control_mode = in[20];
	VCO = in[21];
	Io_ref_amp = in[22];
	Tc = in[23]/2.0;
	fs = in[24]*2.0;
	PI = in[25];
	f = in[26];
	Vs_d_nom = in[27];
	Vs_q_nom = in[28];
	Ic_u = in[29];
	Ic_v = in[30];
//	Ic_w = in[31];
	KP = in[32];
	KI = in[33];
	Vs_u1 = in[34];
	Vs_v1 = in[35];
	Vs_w1 = in[36];
	LPF_V = in[37];
	Vs_k_u_diff[0] = in[38];
	Vs_k_v_diff[0] = in[39];
	Vs_k_w_diff[0] = in[40];
	Vim_u[1] = in[41];
	Vim_u[2] = in[42];
	Vs_k_u_diff[1] = in[43];
	Vs_k_u_diff[2] = in[44];
	Vim_v[1] = in[45];
	Vim_v[2] = in[46];
	Vs_k_v_diff[1] = in[47];
	Vs_k_v_diff[2] = in[48];
	Vim_w[1] = in[49];
	Vim_w[2] = in[50];
	Vs_k_w_diff[1] = in[51];
	Vs_k_w_diff[2] = in[52];

	Vim_u[0] = in[53];
	Vim_v[0] = in[54];
	Vim_w[0] = in[55];
	KP_q = in[56];
	KI_q = in[57];

    // --- U相---
    Vs_k_u_diff[3] = in[58]; //
    Vs_k_u_diff[4] = in[59]; //
    Vs_k_u_diff[5] = in[60]; // 
    Vs_k_u_diff[6] = in[61]; //
    Vs_k_u_diff[7] = in[62]; // 
    Vs_k_u_diff[8] = in[63]; // 

    Vs_k_u_diff[9] = in[94]; //17kHz
    Vs_k_u_diff[10] = in[95]; //20kHz
    Vs_k_u_diff[11] = in[98]; //1kHz
    Vs_k_u_diff[12] = in[100]; //2kHz
    Vs_k_u_diff[13] = in[102]; //3kHz
    Vs_k_u_diff[14] = in[104]; //13kHz
    Vs_k_u_diff[15] = in[106]; //8kHz
    Vs_k_u_diff[16] = in[108]; //9kHz
    Vs_k_u_diff[17] = in[110]; //1MHz

    Vim_u[3] = in[64];
    Vim_u[4] = in[65];
    Vim_u[5] = in[66];
    Vim_u[6] = in[67];
    Vim_u[7] = in[68];
    Vim_u[8] = in[69];

	Vim_u[9] = in[96];//17kHz
    Vim_u[10] = in[97];//20kHz
    Vim_u[11] = in[99];//1kHz
    Vim_u[12] = in[101];//2kHz
    Vim_u[13] = in[103];//3kHz
    Vim_u[14] = in[105];//13kHz	
    Vim_u[15] = in[107];//8kHz
    Vim_u[16] = in[109];//9kHz	
    Vim_u[17] = in[111];//1MHz	
   


	omega = 2 * PI * f;
	a = 1/(2*PI*50*fs + 1);
	//a = 0.8;

    Vc_w = -Vc_u - Vc_v;	//Vc_w = in[5];
	Io_w = -Io_u - Io_v;	//Io_w = in[8];
	IL1_w = -IL1_u - IL1_v;	//IL1_w = in[11];

	if (control_mode == 2.0)
	{
	//	cnt += 1.0;
	if(cnt == 249){
	cnt = 0;
	}
	else{
	cnt = cnt + 1;
	}

	}

	//dq transform

	Vs_a = (2.0/3.0)*(- sqrt(3.0)/(2.0)*Vs_v);//Vsは線間電圧だから線間電圧での変換式を用いている？
	Vs_b = (2.0/3.0)*(1.0/2.0*Vs_u - 1.0/2.0*Vs_w);




//-----------------------疑似dq変換開始------------------------
// quasi dq transform

// ==== U相 ====
// 10MHz
Vre_u[0] = Vs_k_u_diff[0] / (2.0 * 2 * PI * f1_u * Ts);

// 10kHz
Vre_u[3] = Vs_k_u_diff[3] / (2.0 * 2 * PI * f1_u * Ts_10k);
// 6.7kHz 
Vre_u[4] = Vs_k_u_diff[4] / (2.0 * 2 * PI * f1_u * Ts_6k7);

//5kHz
Vre_u[12] = Vs_k_u_diff[12] / (2.0 * 2 * PI * f1_u * Ts_5k);
//3kHz
Vre_u[13] = Vs_k_u_diff[13] / (2.0 * 2 * PI * f1_u * Ts_3k);
//1M
Vre_u[17] = Vs_k_u_diff[17] / (2.0 * 2 * PI * f1_u * Ts_1M);


// ==== U相 dq 変換 ====
// 10MHz
Vs_u_d[0] = Vre_u[0] * cos(vco_u) + Vim_u[0] * sin(vco_u);
Vs_u_q[0] = -Vre_u[0] * sin(vco_u) + Vim_u[0] * cos(vco_u);

// 10kHz
Vs_u_d[3] = Vre_u[3] * cos(vco_u) + Vim_u[3] * sin(vco_u);
Vs_u_q[3] = -Vre_u[3] * sin(vco_u) + Vim_u[3] * cos(vco_u);
// 6.7kHz
Vs_u_d[4] = Vre_u[4] * cos(vco_u) + Vim_u[4] * sin(vco_u);
Vs_u_q[4] = -Vre_u[4] * sin(vco_u) + Vim_u[4] * cos(vco_u);


// 5kHz
Vs_u_d[12] = Vre_u[12] * cos(vco_u) + Vim_u[12] * sin(vco_u);
Vs_u_q[12] = -Vre_u[12] * sin(vco_u) + Vim_u[12] * cos(vco_u);
//3kHz
Vs_u_d[13] = Vre_u[13] * cos(vco_u) + Vim_u[13] * sin(vco_u);
Vs_u_q[13] = -Vre_u[13] * sin(vco_u) + Vim_u[13] * cos(vco_u);
//1MHz
Vs_u_d[17] = Vre_u[17] * cos(vco_u) + Vim_u[17] * sin(vco_u);
Vs_u_q[17] = -Vre_u[17] * sin(vco_u) + Vim_u[17] * cos(vco_u);

// U相 平均
Vs_u_d_ave = (Vs_u_d[17] + Vs_u_d[3] + Vs_u_d[4] + Vs_u_d[12] ) / 4.0;
Vs_u_q_ave = (Vs_u_q[17] + Vs_u_q[3] + Vs_u_q[4] + Vs_u_q[12] ) / 4.0;

Vs_u_d_ave_new[0] = (Vs_u_d[0] + Vs_u_d[3] + Vs_u_d[4] + Vs_u_d[13] ) / 4.0;//10M,10k,6.7k,3k
Vs_u_q_ave_new[0] = (Vs_u_q[0] + Vs_u_q[3] + Vs_u_q[4] + Vs_u_q[13] ) / 4.0;

Vs_u_d_ave_new[1] = (Vs_u_d[0] + Vs_u_d[4] + Vs_u_d[13] ) / 3.0;
Vs_u_q_ave_new[1] = (Vs_u_q[0] + Vs_u_q[4] + Vs_u_q[13] ) / 3.0;



	E_u = Vs_u_q_ave_new[0];
	Int_u += E_u * Ts;
	u_u = KP_q * E_u + KI_q * Int_u;
	f1_u = u_u + f;

	////VCO
	dth_u = 2.0 * PI * f1_u * Ts;
	vco_u += dth_u;

	if (vco_u > 2.0 * PI) vco_u = 0.0;
	else if (vco_u < 0.0)	vco_u += 2.0 * PI;


//----------------疑似dq変換終了--------------------------


//----------------三相PLL制御開始---------------------------

	//dq transform
	Vs_d = Vs_a * cos(vco) + Vs_b * sin(vco);
	Vs_q = -1.0*Vs_a * sin(vco) + Vs_b * cos(vco);

	E = Vs_q;
	Int += E * Ts;
	u = KP * E + KI * Int;
	f1 = u + f;

	//VCO
	dth = 2.0 * PI * f1 * Ts;
	

	if (vco >= 2.0 * PI + dth) vco = 0.0;
	else vco += dth;
	if (vco < 0.0)	vco += 2.0 * PI;

//---------------三相PLL終了------------------------------



	//電流指令値生成
	IL1_u_ref = Io_ref_amp * sin(vco);
	IL1_v_ref = Io_ref_amp * sin(vco - (2.0 * PI / 3.0));
	IL1_w_ref = Io_ref_amp * sin(vco - (4.0 * PI / 3.0));

	IL1_a_ref	=	(2.0/3.0)*(sqrt(3.0)/2.0*IL1_v_ref - sqrt(3.0)/2.0*IL1_w_ref);
	IL1_b_ref	=	(2.0/3.0)*(IL1_u_ref - (1.0/2.0)*IL1_v_ref - (1.0/2.0)*IL1_w_ref);

	Vc_a = (2.0 / 3.0)*((sqrt(3.0) / 2.0) * (Vc_v) - (sqrt(3.0) / 2.0) * (Vc_w));
	Vc_b = (2.0 / 3.0)*(((1.0) * (Vc_u)) - ((1.0 / 2.0) * (Vc_v)) - ((1.0 / 2.0) * (Vc_w)));

	IL1_a = (2.0 / 3.0)*((sqrt(3.0) / 2.0) * (IL1_v) - (sqrt(3.0) / 2.0) * (IL1_w));
	IL1_b = (2.0 / 3.0)*(((1.0) * (IL1_u)) - ((1.0 / 2.0) * (IL1_v)) - ((1.0 / 2.0) * (IL1_w)));

	
	Io_a = IL1_a;//制御用のIo,物理的なIoじゃない
	Io_b = IL1_b;//制御用のIo，物理的なIoじゃない

	if (control_mode == 1)
	{
		z11 = 0.743833347;
		z12 = -6.340668392;
		z13 = 0.256166653;
		zg1 = 12839265.79;


		delta_Ta = (IL1_a_ref - (z11*IL1_a) - (z12*Vc_a) - (z13*Io_a))/zg1;
		delta_Tb = (IL1_b_ref - (z11*IL1_b) - (z12*Vc_b) - (z13*Io_b))/zg1;

		delta_u = delta_Tb;
		delta_v = (-(1.0 / 2.0) * delta_Tb + (sqrt(3.0) / 2.0) * delta_Ta);
		delta_w = (-(1.0 / 2.0) * delta_Tb - (sqrt(3.0) / 2.0) * delta_Ta);

	}

	if (control_mode == 2)
	{

		if (delta_u >= 0.0) {
			if (tri_h > delta_u && tri_h_k1 > tri_h) mode_u = 1;
			if (tri_h < delta_u && tri_h_k1 > tri_h) mode_u = 2;
			if (tri_h < delta_u && tri_h_k1 < tri_h) mode_u = 3;
			if (tri_h > delta_u && tri_h_k1 < tri_h) mode_u = 4;
		}

		if (delta_v >= 0.0) {
			if (tri_h > delta_v && tri_h_k1 > tri_h) mode_v = 1;
			if (tri_h < delta_v && tri_h_k1 > tri_h) mode_v = 2;
			if (tri_h < delta_v && tri_h_k1 < tri_h) mode_v = 3;
			if (tri_h > delta_v && tri_h_k1 < tri_h) mode_v = 4;
		}

		if (delta_w >= 0.0) {
			if (tri_h > delta_w && tri_h_k1 > tri_h) mode_w = 1;
			if (tri_h < delta_w && tri_h_k1 > tri_h) mode_w = 2;
			if (tri_h < delta_w && tri_h_k1 < tri_h) mode_w = 3;
			if (tri_h > delta_w && tri_h_k1 < tri_h) mode_w = 4;
		}

		if (delta_u < 0.0) {
			if (tri_l > delta_u && tri_l_k1 > tri_l) mode_u = 1;
			if (tri_l < delta_u && tri_l_k1 > tri_l) mode_u = 2;
			if (tri_l < delta_u && tri_l_k1 < tri_l) mode_u = 3;
			if (tri_l > delta_u && tri_l_k1 < tri_l) mode_u = 4;
		}

		if (delta_v < 0.0) {
			if (tri_l > delta_v && tri_l_k1 > tri_l) mode_v = 1;
			if (tri_l < delta_v && tri_l_k1 > tri_l) mode_v = 2;
			if (tri_l < delta_v && tri_l_k1 < tri_l) mode_v = 3;
			if (tri_l > delta_v && tri_l_k1 < tri_l) mode_v = 4;
		}

		if (delta_w < 0.0) {
			if (tri_l > delta_w && tri_l_k1 > tri_l) mode_w = 1;
			if (tri_l < delta_w && tri_l_k1 > tri_l) mode_w = 2;
			if (tri_l < delta_w && tri_l_k1 < tri_l) mode_w = 3;
			if (tri_l > delta_w && tri_l_k1 < tri_l) mode_w = 4;
		}

		tri_h_k1 = tri_h;
		tri_l_k1 = tri_l;

		z11 = 0.743833347;
		z12 = -6.340668392;
		z13 = 0.256166653;
		z14 = -0.256166653;
		zg1 = 12839265.79;


		delta_Ta = (IL1_a_ref - (z11*IL1_a) - (z12*Vc_a) - (z13*Io_a) - (z14*Idis_a))/zg1;
		delta_Tb = (IL1_b_ref - (z11*IL1_b) - (z12*Vc_b) - (z13*Io_b) - (z14*Idis_b))/zg1;

		delta_u = delta_Tb;
		delta_v = (-(1.0 / 2.0) * delta_Tb + (sqrt(3.0) / 2.0) * delta_Ta);
		delta_w = (-(1.0 / 2.0) * delta_Tb - (sqrt(3.0) / 2.0) * delta_Ta);
		


		switch (mode_u)
		{
		case 1:
		{
			hold_u = delta_u;

			break;
		}
		case 2:
		{
			delta_u = hold_u;

			break;
		}
		case 3:
		{
			hold_u = delta_u;

			break;
		}
		case 4:
		{
			delta_u = hold_u;

			break;
		}
		}

		switch (mode_v)
		{
		case 1:
		{
			hold_v = delta_v;

			break;
		}
		case 2:
		{
			delta_v = hold_v;

			break;
		}
		case 3:
		{

			hold_v = delta_v;

			break;
		}
		case 4:
		{
			delta_v = hold_v;

			break;
		}
		}

		switch (mode_w)
		{
		case 1:
		{
			hold_w = delta_w;

			break;
		}
		case 2:
		{
			delta_w = hold_w;

			break;
		}
		case 3:
		{

			hold_w = delta_w;

			break;
		}
		case 4:
		{
			delta_w = hold_w;

			break;
		}
		}

	}


	out[0] = Vs_u;
	out[1] = Vs_v;
	out[2] = Vs_w;
	out[3] = Ioref_u;
	out[4] = Ioref_v;
	out[5] = Ioref_w;
	out[6] = Vcref_u;
	out[7] = Vcref_v;
	out[8] = Vcref_w;
	if (control_mode == 1.0)
	{
		out[3] = Ioref_u;
		out[4] = Ioref_v;
		out[5] = Ioref_w;
		out[6] = Vcref_u;
		out[7] = Vcref_v;
		out[8] = Vcref_w;
	}

	if (control_mode == 2.0)
	{
		if (cnt == 0.0)
		{
			out[3] = Ioref_u;
			out[4] = Ioref_v;
			out[5] = Ioref_w;
			out[6] = Vcref_u;
			out[7] = Vcref_v;
			out[8] = Vcref_w;
			out[33] = OC;
			OC = 1;
		}

	}
	//オープン
	if (control_mode == 3.0)
	{
		delta_u =Vs_u1/(Edc*2)*Tc*2;
		delta_v = Vs_v1/(Edc*2)*Tc*2;
		delta_w = Vs_w1/(Edc*2)*Tc*2;
		
	}
	out[9] = Io_u;
	out[10] = Io_v;
	out[11] = Io_w;
	out[12] = Vc_u;
	out[13] = Vc_v;
	out[14] = Vc_w;
	out[15] = delta_u;
	out[16] = delta_v;
	out[17] = delta_w;
	out[18] = vco_u;
	out[19] = vco_v;
	out[20] = vco_w;
	out[21] = Vs_u_d_ave;
	out[22] = Vs_u_q_ave;
	out[23] = Vs_u_d_ave_new[0];
	out[24] = Vs_u_q_ave_new[0];
	out[25] = f1_u;
	//out[26] = Vs_u_q_ave_new[1];
	out[27] = u_u;
	out[28] = u_v;
	out[29] = u_w;
	out[30] = dth_u;
	out[31] = dth_v;
	out[32] = dth_w;
	out[33] = vco_u;
	out[34] = OC_flag;
	out[35] = cnt_OC;
	//out[36] = cnt_OC_flag;
	out[37] = vco;//VCO;
	//out[38] = f21;
	//out[39] = f22;
	//out[40] = f23;
	//out[41] = g21;
	//out[42] = h21;
	out[43]  = IL1_a_ref;
	out[44] = IL1_b_ref;
	out[45] = IL1_u_ref;
	out[46] = IL1_v_ref;
	out[47] = IL1_w_ref;
	out[48] = IL1_a;
	out[49] = IL1_b;
	out[50] = Vs_d;
	out[51] = Vs_q;
	out[52] = f1;
	out[53] = Vre_v[0];
	out[54] = Vre_v[1];
	out[55] = Vre_v[2];
	out[56] = Vre_w[0];
	out[57] = Vre_w[1];
	out[58] = Vre_w[2];
	out[59] = Vs_a;
	out[60] = Vs_b;


    // === U相 Vs (d,q) ===
    out[61] = Vs_u_d[0]; // U相 d軸 50MHz
    out[62] = Vs_u_q[0]; // U相 q軸 50MHz
    out[63] = Vs_u_d[1]; // U相 d軸 25MHz
    out[64] = Vs_u_q[1]; // U相 q軸 25MHz
    out[65] = Vs_u_d[2]; // U相 d軸 12.5MHz
    out[66] = Vs_u_q[2]; // U相 q軸 12.5MHz
    out[67] = Vs_u_d[3]; // U相 d軸 6.25MHz
    out[68] = Vs_u_q[3]; // U相 q軸 6.25MHz
    out[69] = Vs_u_d[4]; // U相 d軸 3.125MHz
    out[70] = Vs_u_q[4]; // U相 q軸 3.125MHz
    out[71] = Vs_u_d[5]; // U相 d軸 1MHz
    out[72] = Vs_u_q[5]; // U相 q軸 1MHz
    out[73] = Vs_u_d[6]; // U相 d軸 500kHz
    out[74] = Vs_u_q[6]; // U相 q軸 500kHz
    out[75] = Vs_u_d[7]; // U相 d軸 6.7kHz
    out[76] = Vs_u_q[7]; // U相 q軸 6.7kHz
    out[77] = Vs_u_d[8]; //
    out[78] = Vs_u_q[8]; // 

    out[115] = Vs_u_d[9]; //17kHz
    out[116] = Vs_u_q[9]; // 17kHz
    out[117] = Vs_u_d[10]; //20kHz
    out[118] = Vs_u_q[10]; // 20k
out[119] = Vs_u_d[11]; // 1k
out[120] = Vs_u_q[11]; // 1k
out[121] = Vs_u_d[12]; // 2k
out[122] = Vs_u_q[12]; // 2k
out[123] = Vs_u_d[13]; // 3k
out[124] = Vs_u_q[13]; // 3k
out[125] = Vs_u_d[14]; // 13k
out[126] = Vs_u_q[14]; // 13k
out[127] = Vs_u_d[15]; // 8k
out[128] = Vs_u_q[15]; // 8k
out[129] = Vs_u_d[16]; // 9k
out[130] = Vs_u_q[16]; // 9k

out[131] = Vs_u_d[17]; // 1M
out[132] = Vs_u_q[17]; // 1M
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