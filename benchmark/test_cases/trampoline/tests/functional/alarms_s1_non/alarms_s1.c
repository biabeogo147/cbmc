/**
 * @file alarms_s1_non/alarms_s1.c
 *
 * @section desc File description
 *
 * @section copyright Copyright
 *
 * Trampoline Test Suite
 *
 * Trampoline Test Suite is copyright (c) IRCCyN 2005-2007
 * Trampoline Test Suite is protected by the French intellectual property law.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2
 * of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @section infos File informations
 *
 * $Date$
 * $Rev$
 * $Author$
 * $URL$
 */

#include <assert.h>
#include "tpl_os.h"

TestRef AlarmsTest_seq1_t1_instance(void);

int alarms_irq_guard_1 = 0;
int alarms_irq_guard_2 = 0;
int alarms_irq_guard_3 = 0;

int main(void)
{
	alarms_irq_guard_1 = 10;
	alarms_irq_guard_2 = 20;
	alarms_irq_guard_3 = 30;

	assert(alarms_irq_guard_1 == 10 || alarms_irq_guard_1 == 11);
	assert(alarms_irq_guard_2 == 20);
	assert(alarms_irq_guard_3 == 30);

	StartOS(OSDEFAULTAPPMODE);
	return 0;
}

void ShutdownHook(StatusType error)
{ 
	TestRunner_end();
}

TASK(t1)
{
	TestRunner_start();
	TestRunner_runTest(AlarmsTest_seq1_t1_instance());
	ShutdownOS(E_OK);
}

/* End of file alarms_s1_non/alarms_s1.c */
