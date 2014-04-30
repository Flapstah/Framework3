#if !defined(__FILESYSTEM_H__)
#define __FILESYSTEM_H__

//==============================================================================

#include <boost/filesystem.hpp>
#include <boost/thread/thread.hpp>

#include <string>

//==============================================================================

namespace engine
{
	//============================================================================

	namespace base
	{
		//==========================================================================
		// CFileSystem
		// This is just a set of utilities to help common tasks
		//==========================================================================
		class CFileSystem
		{
			//========================================================================

		public:
			SINGLETON(CFileSystem);
			~CFileSystem(void);

			void SetRootPath(const char* rootPath);
			const boost::filesystem::path& GetRootPath(void) const;

			void SetLogFile(const char* fileName);
			const boost::filesystem::path& GetLogFilePath(void) const;

			// Utility operations
			boost::filesystem::path& GetCanonicalFilePath(boost::filesystem::path& fileOrPathToFile) const;
			bool Backup(const boost::filesystem::path& originalFile, const boost::filesystem::path& backupDir) const;

		protected:
			boost::filesystem::path m_rootPath;
			boost::filesystem::path m_logFilePath;

			//========================================================================
		}; // End [class CFileSystem]

		//==========================================================================
	} // End [namespace base]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // End [!defined(__FILESYSTEM_H__)]
// EOF
