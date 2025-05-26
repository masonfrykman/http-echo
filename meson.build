project('http-echo', 'cpp', version: '0.1.0')

misc_sources = ['src/misc/config.cpp', 'src/misc/utils.cpp']
server_sources = ['src/server.cpp']
test_sources = ['test/request.cpp']

executable('server', sources: [server_sources, misc_sources])

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')
main_dep = gtest_proj.get_variable('gtest_main_dep')

executable('tests', sources: [test_sources, misc_sources], dependencies: [gtest_dep, gmock_dep, main_dep])