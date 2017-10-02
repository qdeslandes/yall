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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

 #ifndef _YALL
#define _YALL

#include <cstdint>
#include <sstream>
#include <vector>

#include "yall/yall.h"

/*
 * For more informations about how to use the logging system, please refere to the documentation
 * available at https://github.com/Naccyde/yall.
 */

class YallData;
void __yall_cpp_formatter(struct yall_call_data *d, void *args);

struct YallCallParams {
	void (*formatter)(YallData &d, const void *args);
	const void *args;
};

class YallData
{
public:
	// TODO : document this class inside README.md

	std::stringstream header;

	YallData(struct yall_call_data *d) : _data(d)
	{

	}

	std::stringstream &newLine(uint8_t indent=0)
	{
		std::stringstream *ss = new std::stringstream();
		_lines.push_back(ss);

		*ss << std::string(indent, '\t');

		return *ss;
	}

	void __process()
	{
		yall_call_set_header(_data, header.str().c_str());

		for (std::stringstream *s : _lines)
			yall_call_add_line(_data, 0, s->str().c_str());

		for (std::stringstream *s : _lines)
			delete s;
		_lines.clear();
	}

private:
	struct yall_call_data *_data;
	std::vector<std::stringstream *> _lines;
};

class Yall
{
public:
	static Yall &getInstance()
	{
		return _instance;
	}

private:
	Yall()
	{
		yall_init();
	}

	~Yall()
	{
		/*
		* yall_close_all() has no reason to be called in this class
		* as if Yall class is always used, the library will always
		* be closed.
		*/
		yall_close();
	}

	uint32_t _getVersion()
	{
		return yall_get_version();
	}

	std::string _getVersionStr()
	{
		return yall_get_version_string();
	}

	void _setSubsystem(const std::string name, const std::string parent,
		enum yall_log_level log_level, enum yall_output_type output_type,
		const std::string output_file)
	{
		const char *c_parent = parent.empty() ? NULL : parent.c_str();
		const char *c_output = output_file.empty() ? NULL : output_file.c_str();

		// TODO : throw an error if necessary
		yall_set_subsystem(name.c_str(), c_parent, log_level, output_type, c_output);
	}

	void _enableDebug()
	{
		yall_enable_debug();
	}

	void _disableDebug()
	{
		yall_disable_debug();
	}


	bool _isDebug()const
	{
		return yall_is_debug();
	}

	void _enableSubsystem(std::string subsystem_name)
	{
		yall_enable_subsystem(subsystem_name.c_str());
	}

	void _disableSubsystem(std::string subsystem_name)
	{
		yall_enable_subsystem(subsystem_name.c_str());
	}

	void _callLog(std::string subsystem,
		enum yall_log_level log_level,
		std::string function_name,
		void (*formatter)(YallData &d, const void *args),
		const void *args)
	{
		struct YallCallParams p { formatter, args };

		yall_call_log(subsystem.c_str(), log_level, function_name.c_str(), Yall::__yall_cpp_formatter, (const void *)&p);
	}

	static Yall _instance;

public:
	Yall(Yall const &y) = delete;
	void operator=(Yall const &y) = delete;

	static uint32_t getVersion()
	{
		return _instance.getVersion();
	}


	static std::string getVersionStr()
	{
		return _instance._getVersionStr();
	}

	static void setSubsystem(const std::string name, const std::string parent,
		enum yall_log_level log_level, enum yall_output_type output_type,
		const std::string output_file)
	{
		_instance._setSubsystem(name, parent, log_level, output_type, output_file);
	}

	static void enableDebug()
	{
		_instance._enableDebug();
	}

	static void disableDebug()
	{
		_instance._disableDebug();
	}

	static bool isDebug()
	{
		return _instance.isDebug();
	}

	static void enableSubsystem(std::string subsystem_name)
	{
		_instance._enableSubsystem(subsystem_name);
	}

	static void disableSubsystem(std::string subsystem_name)
	{
		_instance._disableSubsystem(subsystem_name);
	}

	void __callLog(std::string subsystem,
		enum yall_log_level log_level,
		std::string function_name,
		void (*formatter)(YallData &d, const void *args),
		const void *args)
	{
		_instance._callLog(subsystem, log_level, function_name, formatter, args);
	}

	static void __yall_cpp_formatter(struct yall_call_data *d, const void *args)
	{
		YallData data{d};

		const struct YallCallParams *p = static_cast<const struct YallCallParams *>(args);
		p->formatter(data, p->args);

		data.__process();
	}
};

Yall Yall::_instance;

#endif