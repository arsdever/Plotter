#ifndef CCMD_H
#define CCMD_H

#include <list>
#include <queue>
#include <string>
#include "cresult.h"

#ifndef nullptr
#define nullptr 0
#endif

typedef std::string Argument;
typedef std::queue<Argument> Arglist;

enum Flags
{
	NoSet = 0,
	Exit = 1
};

// Extern definitions //////////////////////////////////////////////////////////////////////////////////////////////////

extern std::string& toHigher(std::string& string);
extern std::string& toLower(std::string& string);
extern std::istream& inputStream;
extern std::ostream& outputStream;
extern Flags eFlags;

// CMD line interface //////////////////////////////////////////////////////////////////////////////////////////////////

class ICommand : public IType
{
private:
	ICommand * m_pParent;
	ICommand *m_pCMD;
	Arglist *m_slArguments;
	std::string m_strInstanceName;
public:
	enum EErrors
	{
		UnknownCMD = 0x00010000,
		InvalidArgument = 0x00020000
	};

public:
	ICommand(ICommand *pParent = nullptr, std::string strIName = "")
		: IType(strIName)
		, m_pParent(pParent)
	{
		if (pParent != nullptr)
			m_slArguments = pParent->m_slArguments;
		else
			m_slArguments = new Arglist;
	}
	// Destructor																								
	virtual ~ICommand();
	// Get parent pointer
	inline virtual ICommand* GetParent() const { return m_pParent; }
	// Set parent pointer																						
	virtual CResult SetParent(ICommand *pCMDptr);
	inline virtual ICommand* GetCMD() const { return m_pCMD; }
	// Set CMD pointer																							
	virtual CResult SetCMD(ICommand *pCMDptr);
	// Construct and set CMD pointer from name
	virtual CResult SetCMDByName(std::string const& strName);

	// Get argument list																					 	
	inline virtual Arglist * GetArgumentList() const { return m_slArguments; }
	// Get argument from queue
	inline virtual Argument GetArgument(bool bLowCase = false);
	// Append argument to queue
	virtual CResult AppendArgument(Argument const& strArgument);
	// Remove argument from queue
	virtual CResult RemoveArgument();
	// Clear arguments
	virtual void ClearArguments();

	// Parse command
	virtual CResult Parse();
	// Execute CMD																								
	// Should be implemented in derived class																	
	virtual CResult Execute(IType *& pObject);

public:
	// --- Static members --- //

	// Construct a command by name and return it's pointer
	ICommand* ConstructCommand(std::string const& strName);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif