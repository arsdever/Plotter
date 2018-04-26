#include "cresult.h"

CResult::CResult(EResultType eType)
	: IType("result")
	, m_eType(eType)
{}


CResult::~CResult()
{}
