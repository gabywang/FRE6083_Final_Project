#ifndef configure_h
#define configure_h

#include <string>

//to prevent recompile of the whole project because of default parameter change

#define _TRADING_DAT_FILE ".\trading_days.txt"
#define _EPS_FILE ".\eps.xlsx"

#define _MAX_PRICE_BUFF_SIZE 500
#define _TOTAL_STOCK_NUM 1000
#define _GROUP_COUNT 3
#define _SAMPLE_COUNT 5
#define _PRICE_LENGTH 241
#define _SAMPLE_SIZE 100

#define _INDEX_TKR "IWB"
#define _INDEX_START "1/1/1970" // for mat not sure
#define _INDEX_END "11/30/2018"


extern const std::string TRADING_DAT_FILE;
extern const std::string EPS_FILE;

extern const int MAX_PRICE_BUFF_SIZE;
extern const int TOTAL_STOCK_NUM;
extern const int GROUP_COUNT;
extern const int SAMPLE_COUNT;
extern const int PRICE_LENGTH;
extern const int SAMPLE_SIZE;

extern const std::string INDEX_TKR;
extern const std::string INDEX_START;
extern const std::string INDEX_END;
#endif