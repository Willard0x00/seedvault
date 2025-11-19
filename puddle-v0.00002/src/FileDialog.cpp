#include "FileDialog.h"

#include <ShObjIdl.h>
#include <string>

// Dont look at this

std::string open_single_file() {
	char buf[1024] = {0};

	HRESULT hr = CoInitializeEx(NULL, COINITBASE_MULTITHREADED | COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr)) {
		IFileOpenDialog* pfd = NULL;

		HRESULT hr = CoCreateInstance(
			CLSID_FileOpenDialog,
			NULL,
			CLSCTX_INPROC_SERVER,
			__uuidof(pfd),
			reinterpret_cast<void**>(&pfd)
		);

		if (SUCCEEDED(hr)) {
			hr = pfd->Show(NULL);

			if (SUCCEEDED(hr)) {
				IShellItem* psiResult;
				hr = pfd->GetResult(&psiResult);
				if (SUCCEEDED(hr)) {
					PWSTR pszFilePath = NULL;
					hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					if (SUCCEEDED(hr)) {
						size_t i;
						wcstombs_s(&i, buf, 1024, pszFilePath, 1024 - 1);
					}

					CoTaskMemFree(pszFilePath);
					psiResult->Release();
				}
			}
		}

		if (pfd) {
			pfd->Release();
		}
	}

	CoUninitialize();


	return std::string(buf);
}

std::string save_single_file(const char* p_mapName) {
	char buf[1024] = { 0 };

	HRESULT hr = CoInitializeEx(NULL, COINITBASE_MULTITHREADED | COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr)) {
		IFileSaveDialog* pFileSave;

		hr = CoCreateInstance(
			CLSID_FileSaveDialog,
			NULL,
			CLSCTX_ALL,
			IID_IFileSaveDialog,
			reinterpret_cast<void**>(&pFileSave)
		);

		if (SUCCEEDED(hr)) {
			COMDLG_FILTERSPEC dialogFilter[] = {
				{ L"2.18 Map File", L"*.kart" }
			};
			pFileSave->SetFileTypes(1, dialogFilter);

			wchar_t wFileName[1024];
			size_t i;
			mbstowcs_s(&i, wFileName, 1024, p_mapName, strlen(p_mapName) + 1);

			pFileSave->SetFileName(wFileName);
			if (SUCCEEDED(hr)) {
				hr = pFileSave->Show(NULL);
				if (SUCCEEDED(hr)) {
					IShellItem* pItem;
					hr = pFileSave->GetResult(&pItem);
					if (SUCCEEDED(hr)) {
						PWSTR pszFilePath;
						hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
						if (SUCCEEDED(hr)) {
							size_t i;
							wcstombs_s(&i, buf, 1024, pszFilePath, 1024 - 1);
						}

						CoTaskMemFree(pszFilePath);
						pItem->Release();
					}
				}
				pFileSave->Release();
			}
		}
	}

	CoUninitialize();

	return std::string(buf);
}