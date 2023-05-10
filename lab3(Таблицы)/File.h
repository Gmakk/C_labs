#pragma once
#include "Header.h"

int Write(Table* ptab);

int Read(Table* ptab);

FilePlace* Write_Info(InfoType info);

InfoType* Read_Info(FilePlace place);