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

// RUN: %srcroot/test/runtime/run-scheduler-test.py %s -gxx "%gxx" -objroot "%objroot" -ternruntime "%ternruntime" -ternannotlib "%ternannotlib" -nondet

// XXRUN: %srcroot/test/runtime/run-scheduler-test.py %s -gxx "%gxx" -objroot "%objroot" -ternruntime "%ternruntime" -ternannotlib "%ternannotlib"


#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "tern/user.h"

pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cv = PTHREAD_COND_INITIALIZER;
sem_t sem;

void* thread_func(void*) {
  int ret;
  struct timespec ts;
  struct timeval now;

  gettimeofday(&now, NULL);
  ts.tv_sec = now.tv_sec + 1;
  ts.tv_nsec = now.tv_usec * 1000; 
  tern_set_base_timeval(&now);
  ret = sem_timedwait(&sem, &ts);
  assert(ret == -1 && errno == ETIMEDOUT);

  gettimeofday(&now, NULL);
  ts.tv_sec = now.tv_sec + 1;
  ts.tv_nsec = now.tv_usec * 1000;
  tern_set_base_timeval(&now);
  ret = pthread_mutex_timedlock(&mu, &ts);
  assert(ret == ETIMEDOUT);
}


int main(int argc, char *argv[], char *env[]) {
  int ret;
  pthread_t th;

  struct timespec ts;
  struct timeval now;

  sem_init(&sem, 0, 0);
  pthread_mutex_lock(&mu);

  ret = pthread_create(&th, NULL, thread_func, NULL);
  assert(!ret && "pthread_create() failed!");

  gettimeofday(&now, NULL);
  ts.tv_sec = now.tv_sec + 1;
  ts.tv_nsec = now.tv_usec * 1000;
  tern_set_base_timeval(&now);
  ret = sem_timedwait(&sem, &ts);
  assert(ret == -1 && errno == ETIMEDOUT);

  ret = pthread_join(th, NULL);
  assert(!ret && "pthread_join() failed!");

  gettimeofday(&now, NULL);
  ts.tv_sec = now.tv_sec + 1;
  ts.tv_nsec = now.tv_usec * 1000;
  tern_set_base_timeval(&now);
  ret = pthread_cond_timedwait(&cv, &mu, &ts);
  assert(ret == ETIMEDOUT);

  printf("test done\n");

  return 0;
}

// CHECK indicates expected output checked by FileCheck; auto-generated by appending -gen to the RUN command above.
// CHECK:      test done
