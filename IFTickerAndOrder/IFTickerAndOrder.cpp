#include "stdafx.h"
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include "MdSpi.h"
#include "TraderSpi.h"
#include <thread>
#include <iostream>
using namespace std;
// api����
CThostFtdcMdApi* pUserApi;
CThostFtdcTraderApi* pTraderApi;
 //���ò���
//quote
//char FRONT_ADDR_quote[] = "tcp://112.95.158.144:51213"; // ���� 51205  ���� 51213 tcp://172.18.32.125   41205  41213 "tcp://112.95.158.144:51213"
//TThostFtdcBrokerIDType	BROKER_ID = "2084";				// ���͹�˾����    8687 9533
//TThostFtdcInvestorIDType INVESTOR_ID = "999119814";			// Ͷ���ߴ���
//TThostFtdcPasswordType  PASSWORD = "888888";			// �û�����
//char *ppInstrumentID[] = {"cu1512", "cu1601"};			// ���鶩���б�
//int iInstrumentID = 2;									// ���鶩������
////trade
//char  FRONT_ADDR_trade[] = "tcp://112.95.158.144:51205";		// ǰ�õ�ַ tcp://112.95.158.144:51213 ���� 
//TThostFtdcInstrumentIDType INSTRUMENT_ID = "cu1512";	// ��Լ����
//TThostFtdcDirectionType	DIRECTION = THOST_FTDC_D_Sell;	// ��������
//TThostFtdcPriceType	LIMIT_PRICE = 38810; // 38850;				// �۸�


//sinnow 24hous
char FRONT_ADDR_quote[] = "tcp://180.168.146.187:10031"; // ���� 51205  ���� 51213 tcp://172.18.32.125   41205  41213 "tcp://112.95.158.144:51213"
TThostFtdcBrokerIDType	BROKER_ID = "9999";				// ���͹�˾����    8687 9533
TThostFtdcInvestorIDType INVESTOR_ID = "039395";			// Ͷ���ߴ���
TThostFtdcPasswordType  PASSWORD = "yjk19890412";			// �û�����
char *ppInstrumentID[] = { "cu1512", "cu1601" };			// ���鶩���б�
int iInstrumentID = 2;									// ���鶩������

char  FRONT_ADDR_trade[] = "tcp://180.168.146.187:10030";		// ǰ�õ�ַ tcp://112.95.158.144:51213 ���� 
TThostFtdcInstrumentIDType INSTRUMENT_ID = "cu1512";	// ��Լ����
TThostFtdcDirectionType	DIRECTION = THOST_FTDC_D_Sell;	// ��������
TThostFtdcPriceType	LIMIT_PRICE = 38810; // 38850;				// �۸�

//simnow normal


// ������
int iRequestID_quote = 0;
int iRequestID_trade = 0;


void tradeThread()
{
	// ��ʼ��UserApi
	pTraderApi = CThostFtdcTraderApi::CreateFtdcTraderApi();			// ����UserApi
	CTraderSpi* pUserSpi = new CTraderSpi();
	pTraderApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);			// ע���¼���
	pTraderApi->SubscribePublicTopic(THOST_TERT_QUICK);				// ע�ṫ����
	pTraderApi->SubscribePrivateTopic(THOST_TERT_QUICK);				// ע��˽����
	pTraderApi->RegisterFront(FRONT_ADDR_trade);							// connect
	pTraderApi->Init();
	pTraderApi->Join();
	pTraderApi->Release();
}

void quoteThead()
{
	// ��ʼ��UserApi
	pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();			// ����UserApi
	CThostFtdcMdSpi* pUserSpi = new CMdSpi();
	pUserApi->RegisterSpi(pUserSpi);						// ע���¼���
	pUserApi->RegisterFront(FRONT_ADDR_quote);					// connect
	pUserApi->Init();
	pUserApi->Join();
}
int main(void)
{
	cout << "quote thread started......" << endl << endl;
	std::thread QuoteT(quoteThead);
	QuoteT.detach();

	
	//todo: ��Ҫ������һ���߳����µ�
	cout << "trade thead started......" << endl << endl;
	std::thread TradeT(tradeThread);
	TradeT.detach();

	cout << "all threads have been started and will release themselves!" << endl;

	getchar();
	//	pUserApi->Release();
	return 0;
}

