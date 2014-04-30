#include "common/stdafx.h" // log.h included here

#include <time.h>
#include <fstream>

#include "base/filesystem.h"

//==============================================================================

namespace engine
{
	//============================================================================

	namespace base
	{
		//==========================================================================

		CFileSystem::CFileSystem(void)
			: m_rootPath(boost::filesystem::initial_path())
		{
			m_logFilePath = m_rootPath / boost::filesystem::path(LOG_MASTER_NAME ".log");
		}

		//==========================================================================

		CFileSystem::~CFileSystem(void)
		{
		}

		//==========================================================================

		void CFileSystem::SetRootPath(const char* rootPath)
		{
			boost::filesystem::path newRootPath(rootPath);
			m_rootPath = GetCanonicalFilePath(newRootPath);

			// re-point the log file
			SetLogFile(m_logFilePath.filename().generic_string().c_str());
		}

		//==========================================================================

		const boost::filesystem::path& CFileSystem::GetRootPath(void) const
		{
			return m_rootPath;
		}

		//==========================================================================

		void CFileSystem::SetLogFile(const char* fileName)
		{
			boost::filesystem::path newLogFilePath(fileName);
			m_logFilePath = GetCanonicalFilePath(newLogFilePath);
		}

		//==========================================================================

		const boost::filesystem::path& CFileSystem::GetLogFilePath(void) const
		{
			return m_logFilePath;
		}

		//==========================================================================

		boost::filesystem::path& CFileSystem::GetCanonicalFilePath(boost::filesystem::path& fileOrPathToFile) const
		{
			try
			{
				fileOrPathToFile = fileOrPathToFile.is_absolute() ? boost::filesystem::canonical(fileOrPathToFile) : boost::filesystem::canonical(m_rootPath / fileOrPathToFile);
			}

			catch (boost::filesystem::filesystem_error e)
			{
				LOG_ERROR(ENGINE_LOGGER, "%s", e.what());
			}

			return fileOrPathToFile;
		}

		//==========================================================================

		bool CFileSystem::Backup(const boost::filesystem::path& originalFile, const boost::filesystem::path& backupDir) const
		{
			time_t rawTime;
			struct tm* pTimeInfo;
			char buffer[80];
			bool ok = true;

			::time(&rawTime);
			pTimeInfo = localtime(&rawTime);

			try
			{
				// Does the file exist?
				boost::filesystem::path originalFilePath(originalFile);
				boost::filesystem::file_status status = boost::filesystem::status(GetCanonicalFilePath(originalFilePath));
				
				if (boost::filesystem::exists(status) == true)
				{
					// Does the backup path exist?
					boost::filesystem::path backupPath(backupDir);
					status = boost::filesystem::status(GetCanonicalFilePath(backupPath));

					if (boost::filesystem::exists(status) == false)
					{
						boost::filesystem::create_directory(backupPath);
						status = boost::filesystem::status(backupPath);
					}

					if (boost::filesystem::is_directory(backupPath) == true)
					{
						strftime(buffer, sizeof(buffer), "%Y%m%d-%H%M%S_", pTimeInfo);
						boost::filesystem::path backupFilePath(backupPath / (std::string(buffer) + originalFilePath.filename().string()));
						boost::filesystem::rename(originalFilePath, backupFilePath);
					}
				}
			}

			catch (boost::filesystem::filesystem_error e)
			{
				LOG_ERROR(ENGINE_LOGGER, "%s", e.what());
				ok = false;
			}
			
			return ok;
		}

		//==========================================================================
	} // End [namespace base]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF

