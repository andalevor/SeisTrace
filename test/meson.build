create_trace = executable('create_trace', 'create_trace.c',
  include_directories : inc,
  link_with : SeisTrace)
test('Test trace creation', create_trace)
create_header = executable('create_header', 'create_header.c',
  include_directories : inc,
  link_with : SeisTrace)
test('Test trace header creation', create_header)
rw_samples = executable('rw_samples', 'rw_samples.c',
  include_directories : inc,
  link_with : SeisTrace)
test('Test trace samples reading and writing', rw_samples)
rw_header = executable('rw_header', 'rw_header.c',
  include_directories : inc,
  link_with : SeisTrace)
test('Test trace header reading and writing', rw_header)
create_trace_with_header = executable('create_trace_with_header',
  'create_trace_with_header.c',
  include_directories : inc,
  link_with : SeisTrace)
test('Test trace creation with header', create_trace_with_header)
check_header_type = executable('check_header_type', 'check_header_type.c',
  include_directories : inc,
  link_with : SeisTrace)
test('Test trace header type checking', check_header_type)
