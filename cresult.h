#ifndef CRESULT_H
#define CRESULT_H

#include "itype.h"

class CResult : public IType
{
public:
	// Result type enum
	enum EResultType
	{
		// Default invalid value
		Undefined			= 0x00000000,
		// Operation successed
		Success				= 0x00000001,
		// Cast error
		Cast				= 0x00000002,
		// Already was done
		Already				= 0x00000004,
		// Operation fails
		Fail				= 0x00008000,
		// Mask for custom results
		UserMask			= 0xFFFF0000
	};

public:
	// Constructor
	CResult(EResultType eType = Undefined);
	// Set result type
	inline virtual void SetResult(EResultType eType) { m_eType = eType; }
	// Get result type
	inline virtual EResultType GetResult() const { return m_eType; }
	// Check if fail
	inline virtual bool Failure() const { return (m_eType & Fail) == Fail; }
	// Destructor
	virtual ~CResult();

	// Convertation operators
	
	inline operator bool() { return !Failure(); }

protected:
	// Result type
	EResultType m_eType;
};

#endif