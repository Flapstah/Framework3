#include "common/stdafx.h" // log.h included here

#include <time.h>
#include <fstream>

#include "base/filesystem.h"

//==============================================================================

#if defined(TRACE_ENABLE)
#undef TRACE_ENABLE
#endif // defined(TRACE_ENABLE)
#define TRACE_ENABLE false

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
			TRACE(TRACE_ENABLE);

			m_logFilePath = m_rootPath / boost::filesystem::path(LOG_MASTER_NAME ".log");
		}

		//==========================================================================

		CFileSystem::~CFileSystem(void)
		{
			TRACE(TRACE_ENABLE);
		}

		//==========================================================================

		void CFileSystem::SetRootPath(const char* rootPath)
		{
			TRACE(TRACE_ENABLE);

			boost::filesystem::path newRootPath(rootPath);
			m_rootPath = GetCanonicalFilePath(newRootPath);

			// re-point the log file
			SetLogFile(m_logFilePath.filename().generic_string().c_str());
		}

		//==========================================================================

		const boost::filesystem::path& CFileSystem::GetRootPath(void) const
		{
			TRACE(TRACE_ENABLE);

			return m_rootPath;
		}

		//==========================================================================

		void CFileSystem::SetLogFile(const char* fileName)
		{
			TRACE(TRACE_ENABLE);

			boost::filesystem::path newLogFilePath(fileName);
			boost::filesystem::path parent = newLogFilePath.parent_path();
			boost::filesystem::path file = newLogFilePath.filename();
			m_logFilePath = GetCanonicalFilePath(parent) / file;
		}

		//==========================================================================

		const boost::filesystem::path& CFileSystem::GetLogFilePath(void) const
		{
			TRACE(TRACE_ENABLE);

			return m_logFilePath;
		}

		//==========================================================================

		boost::filesystem::path& CFileSystem::GetCanonicalFilePath(boost::filesystem::path& fileOrPathToFile) const
		{
			TRACE(TRACE_ENABLE);

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
			TRACE(TRACE_ENABLE);

			time_t rawTime;
			struct tm* pTimeInfo;
			char buffer[80];
			bool ok = true;

			::time(&rawTime);
			pTimeInfo = localtime(&rawTime);

			try
			{
				// Does the file exist?
				boost::filesystem::file_status status = boost::filesystem::status(originalFile);
				
				if (boost::filesystem::exists(status) == true)
				{
					// Does the backup path exist?
					boost::filesystem::path backupPath(backupDir);
					status = boost::filesystem::status(backupPath);

					if (boost::filesystem::exists(status) == false)
					{
						boost::filesystem::create_directory(backupPath);
						status = boost::filesystem::status(backupPath);
					}

					if (boost::filesystem::is_directory(status) == true)
					{
						strftime(buffer, sizeof(buffer), "%Y%m%d-%H%M%S_", pTimeInfo);
						boost::filesystem::path backupFile(backupPath / (std::string(buffer) + originalFile.filename().string()));
						boost::filesystem::rename(originalFile, backupFile);
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

		bool CFileSystem::ReadLines(const char* name, engine::utility::CCallbackBase& callback)
		{
			TRACE(TRACE_ENABLE);

			// Does the file exist?
			boost::filesystem::path path(name);
			boost::filesystem::file_status status = boost::filesystem::status(GetCanonicalFilePath(path));
			bool ok = false;

			if ((boost::filesystem::exists(status) == true) && (boost::filesystem::is_regular_file(status)))
			{
				std::string line;
				std::ifstream file(path.generic_string().c_str(), std::fstream::in);

				while (file.is_open() && file.good())
				{
					std::getline(file, line);
					callback(reinterpret_cast<void*>(&line));
				}

				file.close();
				ok = true;
			}

			return ok;
		}

		//==========================================================================
	} // End [namespace base]

	//============================================================================
} // End [namespace engine]

//==============================================================================
// EOF

