#include "CStopWatch.h"


CStopWatch::CStopWatch()
{
	Start();
}

CStopWatch::~CStopWatch()
{

}

bool CStopWatch::Start()
{
	return Reset();
}

bool CStopWatch::Reset()
{
	GetTimeOfDay(&m_startTime, NULL);
	return true;
}

timeval CStopWatch::Now()
{
	timeval now;
	GetTimeOfDay(&now, NULL);
	return now;
}

double CStopWatch::ElapsedTime()
{
	timeval now;
	GetTimeOfDay(&now, NULL);
	
	return 1.0*(now.tv_sec-m_startTime.tv_sec) + 1.0*(now.tv_usec-m_startTime.tv_usec)/1000000;
}

double CStopWatch::ElapsedTimeInMill()
{
	timeval now;
	GetTimeOfDay(&now, NULL);

	return (now.tv_sec-m_startTime.tv_sec)*1000 + 1.0*(now.tv_usec-m_startTime.tv_usec)/1000;
}

double CStopWatch::ElapsedTimeInMicro()
{
	timeval now;
	GetTimeOfDay(&now, NULL);

	return (now.tv_sec-m_startTime.tv_sec)*1000000 + 1.0*(now.tv_usec-m_startTime.tv_usec);
}

void CStopWatch::GetTimeOfDay(timeval *tv,void *)
{
#ifdef OS_LINUX
	gettimeofday(tv, NULL);

#elif defined(OS_WINDOWS)
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;

	GetLocalTime(&wtm);
	tm.tm_year     = wtm.wYear - 1900;
	tm.tm_mon     = wtm.wMonth - 1;
	tm.tm_mday     = wtm.wDay;
	tm.tm_hour     = wtm.wHour;
	tm.tm_min     = wtm.wMinute;
	tm.tm_sec     = wtm.wSecond;
	tm. tm_isdst    = -1;
	clock = mktime(&tm);
	tv->tv_sec = clock;
	tv->tv_usec = wtm.wMilliseconds * 1000;
#endif
}