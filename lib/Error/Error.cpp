
#include <WString.h>
#include "Error.h"

Error::Error(bool isError_, String errorMsg_){
  isError = isError_;
  errorMsg = errorMsg_;
}

bool Error::hasError() const {
  return isError;
}

String Error::getErrorMsg() const {
  return errorMsg;
}
