/*
 * MIT License
 *
 * Copyright (c) 2017 Quentin "Naccyde" Deslandes.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _YALL_HPP
#define _YALL_HPP

#include <cstdint>
#include <sstream>
#include <vector>
#include <exception>
#include <sstream>

#include "yall/yall.h"

class YallData;

struct YallCallParams {
	void (*formatter)(YallData &d, const void *args);
	const void *args;
};

class YallException : public std::exception
{
public:
	YallException(yall_error err)
	{
		num = err;

		std::ostringstream oss;
		oss << yall_strerror(err);
		msg = oss.str();
	}

	virtual const char *what() const throw()
	{
		return msg.c_str();
	}

private:
	std::string msg;
	int num;
};

class YallData
{
public:
	std::stringstream header;

	YallData(struct yall_call_data *d) : _data(d)
	{

	}

	std::stringstream &newLine(uint8_t indent=0)
	{
		std::stringstream *ss = new std::stringstream();
		_lines.push_back(ss);

		*ss << std::string(indent * yall_config_get_tab_width(), ' ');

		return *ss;
	}

	void __process()
	{
		yall_call_set_header(_data, header.str().c_str());

		for (std::stringstream *ss : _lines)
		{
			std::string s = ss->str();
			yall_call_add_line(_data, 0, s.c_str());
		}

		for (std::stringstream *ss : _lines)
			delete ss;
		
		_lines.clear();
	}

private:
	struct yall_call_data *_data;
	std::vector<std::stringstream *> _lines;
};

class YallConfig
{
public:
	void setStdHeaderTemplate(std::string stdHeaderTemplate)
	{
		yall_config_set_std_header_template(stdHeaderTemplate.c_str());
	}

	std::string getStdHeaderTemplate()
	{
		return std::string(yall_config_get_std_header_template());
	}

	void resetStdHeaderTemplate()
	{
		yall_config_reset_std_header_template();
	}

	void setCallHeaderTemplate(std::string callHeaderTemplate)
	{
		yall_config_set_call_header_template(callHeaderTemplate.c_str());
	}

	std::string getCallHeaderTemplate()
	{
		return std::string(yall_config_get_call_header_template());
	}

	void resetCallHeaderTemplate()
	{
		yall_config_reset_call_header_template();
	}

	void setTabWidth(uint8_t tabWidth)
	{
		yall_config_set_tab_width(tabWidth);
	}

	uint8_t getTabWidth()
	{
		return yall_config_get_tab_width();
	}

	void resetTabWidth()
	{
		yall_config_reset_tab_width();
	}
};

class Yall
{
public:
	/*
	 * Version infos
	 */
	static uint32_t getVersion()
	{
		return yall_get_version();
	}

	static std::string getVersionString()
	{
		return std::string(yall_get_version_string());
	}

	/*
	 * Library setup
	 */
	static void init()
	{
		yall_error err = yall_init();

		if (YALL_SUCCESS != err)
			throw YallException(err);
	}

	static uint16_t isInit(void)
	{
		return yall_is_init();
	}

	static void _log(std::string subsystem, enum yall_log_level log_level, std::string function, std::string filename, int32_t line, std::string msg)
	{
		yall_log(subsystem.c_str(), log_level, function.c_str(), filename.c_str(), line, msg.c_str());
	}

	static void _callLog(std::string subsystem, enum yall_log_level log_level, std::string function_name, std::string filename, int32_t line, void (*formatter)(YallData &d, const void *args), const void *args)
	{
		struct YallCallParams p { formatter, args };

		yall_call_log(subsystem.c_str(), log_level, function_name.c_str(), filename.c_str(), line, Yall::__yall_cpp_formatter, (const void *)&p);
	}

	static void setSubsystem(std::string name, std::string parent, enum yall_log_level log_level, enum yall_output_type output_type, std::string output_file)
	{
		yall_error err = yall_set_subsystem(name.c_str(), parent.c_str(), log_level, output_type, output_file.c_str());

		if (YALL_SUCCESS != err)
			throw YallException(err);
	}

	static void close()
	{
		yall_close();
	}

	static void closeAll()
	{
		yall_close_all();
	}

	/*
	 * Manage subsystem
	 */
	static void disableSubsystem(std::string subsystem)
	{
		yall_disable_subsystem(subsystem.c_str());
	}

	static void enableSubsystem(std::string subsystem)
	{
		yall_enable_subsystem(subsystem.c_str());
	}

	static void showSubsystemsTree()
	{
		yall_show_subsystems_tree();
	}

	/*
	 * Configuration
	 */
	static YallConfig &config()
	{
		static YallConfig config;

		return config;
	}

	/*
	 * Debug
	 */
	static void enableDebug()
	{
		yall_enable_debug();
	}

	static void disableDebug()
	{
		yall_disable_debug();
	}

	static bool isDebug()
	{
		return yall_is_debug();
	}

	/*
	 * Error management
	 */
	static std::string _strError(yall_error err)
	{
		return std::string(yall_strerror(err));
	}

	static void __yall_cpp_formatter(struct yall_call_data *d, const void *args)
	{
		YallData data { d };

		const struct YallCallParams *p = static_cast<const struct YallCallParams *>(args);
		p->formatter(data, p->args);

		data.__process();
	}
};

#endif