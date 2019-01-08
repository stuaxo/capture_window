// capture_window.cpp : Defines the entry point for the application.
//

#include "capture_window.h"
#include "atlimage.h"
#include <Gdiplusimaging.h>

cxxopts::ParseResult
parse(int argc, char* argv[])
{
	try
	{
		cxxopts::Options options(argv[0], " - capture window as image");
		options
			.positional_help("[optional args]")
			.show_positional_help();

		options
			.allow_unrecognised_options()
			.add_options()
			("d,decorations", "Capture window decorations", cxxopts::value<bool>()->default_value("false"))
			("c,clsid", "Window class identifier", cxxopts::value<std::string>()->default_value(""))
			("t,title", "Window title", cxxopts::value<std::string>()->default_value(""))
			("o,output", "Output filename", cxxopts::value<std::string>())
			("l,list", "List windows", cxxopts::value<std::string>())
			("h,help", "Print help")
			;

		options.parse_positional({ "clsid", "title" });

		auto result = options.parse(argc, argv);

		if (result.count("help") || 
			(result.count("clsid") + result.count("title") == 0))
		{
			std::cout << options.help() << std::endl;
			exit(0);
		}

		return result;

	}
	catch (const cxxopts::OptionException& e)
	{
		std::cout << "error parsing options: " << e.what() << std::endl;
		exit(1);
	}
}

HBITMAP CaptureWindowBitmap(HWND hWnd, bool clientOnly)
{
	RECT rc;
	GetClientRect(hWnd, &rc);

	HDC hdcScreen = GetDC(NULL);
	HDC hdc = CreateCompatibleDC(hdcScreen);
	HBITMAP hbmp = CreateCompatibleBitmap(hdcScreen, rc.right - rc.left, rc.bottom - rc.top);
	SelectObject(hdc, hbmp);

	PrintWindow(hWnd, hdc, clientOnly ? PW_CLIENTONLY : PW_RENDERFULLCONTENT);

	DeleteDC(hdc);
	ReleaseDC(NULL, hdcScreen);

	return hbmp;
}

void SaveHBitmap(HBITMAP hbmpImage, LPCTSTR filename)
{
	CImage image;
	image.Attach(hbmpImage);
	image.Save(filename);
}

using namespace std;

bool capture_window(string clsid, string title, string filename, bool decorations)
{
	HBITMAP bmp;
	HWND hWnd = FindWindow(clsid.empty() ? 0 : clsid.c_str(), title.empty() ? 0 : title.c_str());
	if (hWnd == 0) 
	{
		return false;
	}
	else
	{
		bmp = CaptureWindowBitmap(hWnd, !decorations);
		std::cout << filename.c_str() << endl;
		SaveHBitmap(bmp, filename.c_str());
		return true;
	}

}

using namespace std;

int main(int argc, char* argv[])
{
	std::string filename;
	auto result = parse(argc, argv);
	auto arguments = result.arguments();

	if (result.count("list"))
	{

	}

	if (result.count("title") || result.count("clsid"))
	{
		if (result.count("output"))
		{
			filename = result["output"].as<string>();
		}
		else
		{
			if (result.count("title"))
			{
				filename = result["title"].as<string>() + ".png";
			}
			else if (result.count("clsid"))
			{
				filename = result["clsid"].as<string>() + ".png";
			}
			else
			{
				abort();
			}
			if (! capture_window(result["clsid"].as<string>(),
					result["title"].as<string>(),
					filename,
					result["decorations"].as<bool>()))
			{
				std::cout << "Window not found." << std::endl;
				exit(2);
			}
		}
		exit(0);
	}

	return 0;
}
