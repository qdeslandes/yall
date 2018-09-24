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

#ifndef _YALL_STATUS_H
#define _YALL_STATUS_H

/**
 * \enum yall_subsys_status
 * \brief Contain the different statuses of a yall subsystem.
 * \var yall_subsys_status::yall_subsys_enable
 *	\brief Subsystem is enable and can be used to write log messages.
 * \var yall_subsys_status::yall_subsys_disable
 *	\brief Subsystem is disable, all log messages will be discarded.
 * \var yall_subsys_status::yall_inherited_status
 *	\brief Subsystem use its parent's status.
 */
enum yall_subsys_status {
	yall_subsys_enable,
	yall_subsys_disable,
	yall_inherited_status
};

#endif
