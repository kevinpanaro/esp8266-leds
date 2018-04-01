#ifndef ERROR_H
#define ERROR_H

#include <WString.h>


class Error
{
private:
  bool isError;
  String errorMsg;

public:
  Error(bool isError, String errorMsg);
  bool hasError() const;
  String getErrorMsg() const;
};

#endif
