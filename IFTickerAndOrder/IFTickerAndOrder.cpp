#include "stdafx.h"
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include "MdSpi.h"
#include "TraderSpi.h"
#include <thread>
#include <iostream>
using namespace std;
// api对象
CThostFtdcMdApi* pUserApi;
CThostFtdcTraderApi* pTraderApi;
 //配置参数
//quote
//char FRONT_ADDR_quote[] = "tcp://112.95.158.144:51213"; // 交易 51205  行情 51213 tcp://172.18.32.125   41205  41213 "tcp://112.95.158.144:51213"
//TThostFtdcBrokerIDType	BROKER_ID = "2084";				// 经纪公司代码    8687 9533
//TThostFtdcInvestorIDType INVESTOR_ID = "999119814";			// 投资者代码
//TThostFtdcPasswordType  PASSWORD = "888888";			// 用户密码
//char *ppInstrumentID[] = {"cu1512", "cu1601"};			// 行情订阅列表
//int iInstrumentID = 2;									// 行情订阅数量
////trade
//char  FRONT_ADDR_trade[] = "tcp://112.95.158.144:51205";		// 前置地址 tcp://112.95.158.144:51213 行情 
//TThostFtdcInstrumentIDType INSTRUMENT_ID = "cu1512";	// 合约代码
//TThostFtdcDirectionType	DIRECTION = THOST_FTDC_D_Sell;	// 买卖方向
//TThostFtdcPriceType	LIMIT_PRICE = 38810; // 38850;				// 价格


//sinnow 24hous
char FRONT_ADDR_quote[] = "tcp://180.168.146.187:10031"; // 交易 51205  行情 51213 tcp://172.18.32.125   41205  41213 "tcp://112.95.158.144:51213"
TThostFtdcBrokerIDType	BROKER_ID = "9999";				// 经纪公司代码    8687 9533
TThostFtdcInvestorIDType INVESTOR_ID = "039395";			// 投资者代码
TThostFtdcPasswordType  PASSWORD = "yjk19890412";			// 用户密码
char *ppInstrumentID[] = { "cu1512", "cu1601" };			// 行情订阅列表
int iInstrumentID = 2;									// 行情订阅数量

char  FRONT_ADDR_trade[] = "tcp://180.168.146.187:10030";		// 前置地址 tcp://112.95.158.144:51213 行情 
TThostFtdcInstrumentIDType INSTRUMENT_ID = "cu1512";	// 合约代码
TThostFtdcDirectionType	DIRECTION = THOST_FTDC_D_Sell;	// 买卖方向
TThostFtdcPriceType	LIMIT_PRICE = 38810; // 38850;				// 价格

//simnow normal


// 请求编号
int iRequestID_quote = 0;
int iRequestID_trade = 0;


void tradeThread()
{
	// 初始化UserApi
	pTraderApi = CThostFtdcTraderApi::CreateFtdcTraderApi();			// 创建UserApi
	CTraderSpi* pUserSpi = new CTraderSpi();
	pTraderApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);			// 注册事件类
	pTraderApi->SubscribePublicTopic(THOST_TERT_QUICK);				// 注册公有流
	pTraderApi->SubscribePrivateTopic(THOST_TERT_QUICK);				// 注册私有流
	pTraderApi->RegisterFront(FRONT_ADDR_trade);							// connect
	pTraderApi->Init();
	pTraderApi->Join();
	pTraderApi->Release();
}

void quoteThead()
{
	// 初始化UserApi
	pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();			// 创建UserApi
	CThostFtdcMdSpi* pUserSpi = new CMdSpi();
	pUserApi->RegisterSpi(pUserSpi);						// 注册事件类
	pUserApi->RegisterFront(FRONT_ADDR_quote);					// connect
	pUserApi->Init();
	pUserApi->Join();
}
int main(void)
{
	cout << "quote thread started......" << endl << endl;
	std::thread QuoteT(quoteThead);
	QuoteT.detach();

	
	//todo: 需要另外起一条线程来下单
	cout << "trade thead started......" << endl << endl;
	std::thread TradeT(tradeThread);
	TradeT.detach();

	cout << "all threads have been started and will release themselves!" << endl;

	getchar();
	//	pUserApi->Release();
	return 0;
}

