CU_SET_PATH("CMAKE_MOD_BOSS_ANNOUNCER_DIR" "${CMAKE_CURRENT_LIST_DIR}")

AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/mod_boss_announcer.cpp")

AC_ADD_SCRIPT_LOADER("Boss_Announcer" "${CMAKE_CURRENT_LIST_DIR}/src/loader_boss_announcer.h")

AC_ADD_CONFIG_FILE("${CMAKE_CURRENT_LIST_DIR}/conf/mod_boss_announcer.conf.dist")
