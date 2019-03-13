/*********************************************************************************************
������	8 �������� C ����
Ӳ����	STC12C2052AD��12MHz
���ڣ�	2019-03-09
���ߣ�	����
�ʼ���	wangkai.geo@qq.com
��վ��	https://geokylin.github.io
�汾��
����V1.0 - �㷨������ע��
/*********************************************************************************************/

#include <STC12C2052AD.H> //STC12C2052AD��Ƭ��ͷ�ļ�����STC-ISP��������
#define STATUS P1 //���а�����״̬��8������ʹ�õ�1��I/O����P1��ÿ��I/O�ӿ���8������0-7

// ��������
sbit SPEAKER = P3^7; //������������P3.7
unsigned char KEY; //�����µİ�����0-7
unsigned char tTH0; //16λ��ʱ���ĸ�8λ�����ڴ��ݸ��жϺ���
unsigned char tTL0; //16λ��ʱ���ĵ�8λ�����ڴ��ݸ��жϺ���
unsigned int code music[]={ //ʮ��ƽ�����������飬code�ؼ��ֶ�������Ĵ洢λ���ǳ���洢��
64021,64103,64260,64400, //e1, f1, g1, a1
64524,64580,64684,64777, //b1, c2, d2, e2
64820,64898,64968,65030, //f2, g2, a2, b2
65058,65110,65157,65178  //c3, d3, e3, f3
};

// ������
void main(void){
	TMOD=0x01; //���ö�ʱ��T0��ģʽΪ16λ��ʱ��
	ET0=1; //������ʱ��T0�ж�
	EA=1; //����CPU�����жϣ����жϿ���
	STATUS = 0xff; //���������ŵ�λ����Ϊ�ߵ�λ1
	while(1){
		if(STATUS != 0xff){ //�а�����ͨ�����
			switch(~STATUS){ //�жϽ�ͨ�İ�����������ͨ������Ϊ�͵�λ0���䷴״̬Ϊ1
				case 0x01: //����ͨP1.0��STATUS��8��λ�ķ�״̬Ϊ 0000 0001
					KEY = 7; //����Ϊ e2
					break;
				case 0x02: //����ͨP1.1��STATUS��8��λ�ķ�״̬Ϊ 0000 0010
					KEY = 6; //����Ϊ d2
					break;
				case 0x04: //����ͨP1.2��STATUS��8��λ�ķ�״̬Ϊ 0000 0100
					KEY = 5; //����Ϊ c2
					break;
				case 0x08: //����ͨP1.3��STATUS��8��λ�ķ�״̬Ϊ 0000 1000
					KEY = 4; //����Ϊ b1
					break;
				case 0x10: //����ͨP1.4��STATUS��8��λ�ķ�״̬Ϊ 0001 0000
					KEY = 3; //����Ϊ a1
					break;
				case 0x20: //����ͨP1.5��STATUS��8��λ�ķ�״̬Ϊ 0010 0000
					KEY = 2; //����Ϊ g1
					break;
				case 0x40: //����ͨP1.6��STATUS��8��λ�ķ�״̬Ϊ 0100 0000
					KEY = 1; //����Ϊ f1
					break;
				case 0x80: //����ͨP1.7��STATUS��8��λ�ķ�״̬Ϊ 1000 0000
					KEY = 0; //����Ϊ e1
					break;
			}
			tTH0=music[KEY]/256; //ȡmusic����������KEY��Ӧ������16���Ƶĸ�8λ
			tTL0=music[KEY]%256; //ȡmusic����������KEY��Ӧ������16���Ƶĵ�8λ
			TR0=1; //������ʱ��T0
		}else{ //û�а�����ͨ�������
			SPEAKER = 1; //����P3.7Ϊ�ߵ�λ��������������
			TR0=0; //�رն�ʱ��T0
		}
	}
}

//��ʱ��T0���жϺ���
void t0(void) interrupt 1 using 0{ //interrupt 1ָ���Ƕ�ʱ��T0���жϺ�����using 0��ʾ���õ�0��Ĵ���
	TH0=tTH0; //���ö�ʱ��T0�ĸ�8λ
	TL0=tTL0; //���ö�ʱ��T0�ĵ�8λ
	SPEAKER=~SPEAKER; //����P3.7Ϊ�͵�λ������
}