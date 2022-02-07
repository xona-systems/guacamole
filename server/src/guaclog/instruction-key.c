/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include "config.h"
#include "log.h"
#include "parse.h"
#include "state.h"

#include <guacamole/timestamp.h>

#include <stdbool.h>
#include <stdlib.h>

int guaclog_handle_key(guaclog_state* state, int argc, char** argv) {

    /* Verify argument count */
    if (argc < 3) {
        guaclog_log(GUAC_LOG_WARNING, "\"key\" instruction incomplete");
        return 1;
    }

    /* Parse arguments */
    int keysym = atoi(argv[0]);
    bool pressed = (atoi(argv[1]) != 0);
    guac_timestamp timestamp = guacenc_parse_timestamp(argv[2]);

    /* Set initial timestamp, if needed */
    if (state->ts_check_first == -1) {
        state->ts_first = timestamp;
        state->ts_check_first = 0;
    }

    /* Update current timestamp */
    state->ts_keys_current = timestamp;

    /* Update interpreter state accordingly */
    return guaclog_state_update_key(state, keysym, pressed);
}

