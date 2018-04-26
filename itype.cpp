#include "itype.h"
#include "cresult.h"

CResult IType::SetInstanceName(std::string const& strName)
{
	m_strInstanceName = strName;
	return CResult::Success;
}