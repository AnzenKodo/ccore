#ifndef STD_CORE_H
#define STD_CORE_H

// Units
//======

#define KB(n)  (((U64)(n)) << 10)
#define MB(n)  (((U64)(n)) << 20)
#define GB(n)  (((U64)(n)) << 30)
#define TB(n)  (((U64)(n)) << 40)
#define Thousand(n)   ((n)*1000)
#define Million(n)    ((n)*1000000)
#define Billion(n)    ((n)*1000000000)

// Clamps, Mins, Maxes
//====================

#define Min(A,B) (((A)<(B))?(A):(B))
#define Max(A,B) (((A)>(B))?(A):(B))
#define ClampTop(A,X) Min(A,X)
#define ClampBot(X,B) Max(X,B)
#define Clamp(A,X,B) (((X)<(A))?(A):((X)>(B))?(B):(X))

// Time
//=====

typedef enum WeekDay {
  WeekDay_sun,
  WeekDay_mon,
  WeekDay_tue,
  WeekDay_wed,
  WeekDay_thu,
  WeekDay_fri,
  WeekDay_sat,
  WeekDay_COUNT,
} WeekDay;

typedef enum Month {
  Month_jan,
  Month_feb,
  Month_mar,
  Month_apr,
  Month_may,
  Month_jun,
  Month_jul,
  Month_aug,
  Month_sep,
  Month_oct,
  Month_nov,
  Month_dec,
  Month_COUNT,
} Month;

typedef struct DateTime
{
  U16 micro_sec; // [0,999]
  U16 msec; // [0,999]
  U16 sec;  // [0,60]
  U16 min;  // [0,59]
  U16 hour; // [0,24]
  U16 day;  // [0,30]
  union
  {
    WeekDay week_day;
    U32 wday;
  };
  union
  {
    Month month;
    U32 mon;
  };
  U32 year; // 1 = 1 CE, 0 = 1 BC
} DateTime;


#endif STD_CORE_H
