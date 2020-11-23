#include "TM4C123.h"                    // Device header

#define PID_st		PID_Sample_Time
#define PID_MAX		2
#define PID_MIN		2
#define PID_Cal		1
#define PID_Kp		1.2
#define PID_Ki		1
#define PID_Kd		1

typedef struct{
	int Sensor;
	int Setpoint;
	double Kp;
	double Ki;
	double Kd;
	double CtrlOut[2];
	double Error[3];
	double st;
	int OutMax;
	int OutMin;
	int Cal;
	
} PID_Param;

extern uint32_t SysClk;
extern double PID_Sample_Time;
double OUT_M1[2], *OUT_M2[2];
double *Error_M1[3], *Error_M2[3];
PID_Param M1, M2;

double PID(PID_Param *Param );

void TIMER0A_Handler(void)
{
	M1.Sensor   = 1;
	M1.Setpoint = 2;
	M1.Kp				= PID_Kp;
	M1.Ki				= PID_Ki;
	M1.Kd				= PID_Kd;
	M1.st				= PID_st;
	M1.OutMax		= PID_MAX;
	M1.OutMin		= PID_MIN;
	M1.Cal			= PID_Cal;
	
	M2.Sensor   = 1;
	M2.Setpoint = 2;
	M2.Kp				= PID_Kp;
	M2.Ki				= PID_Ki;
	M2.Kd				= PID_Kd;
	M2.st				= PID_st;
	M2.OutMax		= PID_MAX;
	M2.OutMin		= PID_MIN;
	M2.Cal			= PID_Cal;
	
	PID(&M1);
	PID(&M2);
//	GPIOF->DATA ^= 1UL<<3;
	TIMER0->ICR = 0x01;
}

double PID(PID_Param *Param )
{
	double Mem0=0, Mem1=0, Mem2=0;
	
	Mem0 = Param->Ki*Param->st/2.0 + Param->Kd/Param->st + Param->Kp;
	Mem1 = Param->Ki*Param->st/2.0 - 2.0*Param->Kd/Param->st - Param->Kp;
	Mem2 = Param->Kd/Param->st;
	
	Param->Error[0]	 = Param->Setpoint - Param->Sensor;
	Param->CtrlOut[0] = Param->CtrlOut[1] + Mem0* Param->Error[0] + Mem1* Param->Error[1] + Mem2* Param->Error[2];
	
	Param->CtrlOut[1] = Param->CtrlOut[0];
	Param->Error[2]	 = Param->Error[1];
	Param->Error[1]	 = Param->Error[0];
	
	if(Param->CtrlOut[0]>= Param->OutMax){
		Param->CtrlOut[0]=Param->OutMax; Param->CtrlOut[1]=Param->OutMax;}
	else if(Param->CtrlOut[0]<= Param->OutMin){
		Param->CtrlOut[0]=Param->OutMin; Param->CtrlOut[1]=Param->OutMin;}
	
	return Param->CtrlOut[0]*Param->Cal;
}
