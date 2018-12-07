#ifndef configure_h
#define configure_h

#include <string>

//to prevent recompile of the whole project because of default parameter change

#define _TRADING_DAT_FILE ".\trading_days.txt"
#define _EPS_FILE "C:\\Users\\Rex Hoo\\Documents\\workspace\\financial_computing\\FRE6083_Final_Project\\group_project\\RIY_Data.csv"

#define _MAX_PRICE_BUFF_SIZE 500
#define _TOTAL_STOCK_NUM 1000
#define _SAMPLE_COUNT 5
#define _GROUP_COUNT 3
#define _PRICE_LENGTH 241
#define _SAMPLE_SIZE 100

#define _INDEX_TKR "IWB"
#define _INDEX_START "1/1/1970" // for mat not sure
#define _INDEX_END "11/30/2018"

#define _EPS_INDEX_COL 0
#define _EPS_EPS_COL 1
#define _EPS_EST_EPS_COL 2
#define _EPS_RE_DATE_COL 3
#define _EPS_START_ROW 1

#define _BAND1 .10
#define _BAND2 .05
#define _BAND3 .95
#define _BAND4 .90

extern const std::string TRADING_DAT_FILE;
extern const std::string EPS_FILE;

extern const int MAX_PRICE_BUFF_SIZE;
extern const int TOTAL_STOCK_NUM;
extern const int SAMPLE_COUNT;
extern const int GROUP_COUNT;
extern const size_t PRICE_LENGTH;
extern const int SAMPLE_SIZE;

extern const std::string INDEX_TKR;
extern const std::string INDEX_START;
extern const std::string INDEX_END;

extern const int EPS_INDEX_COL;
extern const int EPS_EPS_COL;
extern const int EPS_EST_EPS_COL;
extern const int EPS_RE_DATE_COL;
extern const int EPS_START_ROW;

extern const double BAND1;
extern const double BAND2;
extern const double BAND3;
extern const double BAND4;
#endif