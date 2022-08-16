/* Additional Modification Copyright (c) 2016-2018 North Carolina State University.
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions and use are permitted for internal research purposes only, 
 * and commercial use is strictly prohibited under this license. Inquiries 
 * regarding commercial use should be directed to the Office of Technology 
 * Transfer at North Carolina State University, 919‐515‐7199, https://research.
 * ncsu.edu/otcnv/contact/, techtransfer@ncsu.edu.
 * 
 * 2. Commercial use means the sale, lease, export, transfer, conveyance or other 
 * distribution to a third party for financial gain, income generation or other 
 * commercial purposes of any kind, whether direct or indirect. Commercial use 
 * also means providing a service to a third party for financial gain, income 
 * generation or other commercial purposes of any kind, whether direct or 
 * indirect.
 * 
 * 3. Redistributions of source code must retain the above copyright notice, this 
 * list of conditions and the following disclaimer.
 * 
 * 4. Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation and/
 * or other materials provided with the distribution.
 * 
 * 5. The names “North Carolina State University”, “NCSU” and any trade‐name,
 * personal name, trademark, trade device, service mark, symbol, image, icon, or 
 * any abbreviation, contraction or simulation thereof owned by North Carolina 
 * State University must not be used to endorse or promote products derived from 
 * this software without prior written permission. For written permission, please
 * contact trademarks@ncsu.edu.
 * 
 * Disclaimer: THIS SOFTWARE IS PROVIDED “AS IS” AND ANY EXPRESSED OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO 
 * EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR ITS CONTRIBUTORS BE LIABLE FOR 
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (
 * INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

/* Additional Modification by : Qi Zhao (qzhao6@ncsu.edu), Zhengyi Qiu (zqiu2@ncsu.edu), Guoliang Jin (guoliang_jin@ncsu.edu) */

/* Copyright (c) 2013,  Regents of the Columbia University 
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other 
 * materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Authors: Heming Cui (heming@cs.columbia.edu), Junfeng Yang (junfeng@cs.columbia.edu) -*- Mode: C++ -*- */
#include <pthread.h>
#include <sys/time.h>

#ifndef __TERN_COMMON_USER_H
#define __TERN_COMMON_USER_H

/* users manually insert these macros to their programs */

#ifdef __cplusplus
extern "C" {
#endif

  /// mark memory [@addr, @addr+@nbytes) as symbolic; @symname names this
  /// symbolic memory for debugging
  void tern_symbolic(void *addr, int nbytes, const char *symname);

  /// for server programs, users manually insert these two methods at
  /// beginning and the end of the processing of a user request.  @addr
  /// and @nbytes mark the relevant request data as symbolic.
  void tern_task_begin(void *addr, int nbytes, const char *name);
  void tern_task_end(void);

  /// New programming primitives to get better performance without affecting
  /// logics of applications.
  void soba_init(long opaque_type, unsigned count, unsigned timeout_turns);
  void soba_destroy(long opaque_type);
  void tern_lineup_start(long opaque_type);
  void tern_lineup_end(long opaque_type);
  void soba_wait(long opaque_type);

  void tern_workload_start(long opaque_type, unsigned workload_hint);
  void tern_workload_end(long opaque_type);

  void pcs_enter();
  void pcs_exit();
  void no_wait_pcs_enter();
  void no_wait_pcs_exit();
  void slock_next_n(int slock_next_n);
  void scwf_ignore_variable(int isSet);
  void propose_thread_role(pthread_t th, void *(*role_func)(void*));
  void tern_dummy_sync();
  void tern_detach();
  void pcs_barrier_exit(int bar_id, int cnt);

  void mark_task_start(int task_id);
  void mark_task_end(int task_id);
  void unmark_task(int task_id);

  /// Set thread local base time. This is for pthread_cond_timedwait(), sem_timedwait() and pthread_mutex_timedlock().
  void tern_set_base_timespec(struct timespec *ts);
  void tern_set_base_timeval(struct timeval *tv);

  void tern_set_iter(long i);

  void ext_get_turn();
  void ext_put_turn();

  long time_to_long(struct timeval * tv);
  long tern_time_diff(struct timeval *end, struct timeval *start);


#ifdef __cplusplus
}
#endif

#endif
