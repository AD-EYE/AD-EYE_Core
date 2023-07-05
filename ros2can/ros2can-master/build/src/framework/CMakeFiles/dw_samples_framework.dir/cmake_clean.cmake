file(REMOVE_RECURSE
  "libdw_samples_framework.pdb"
  "libdw_samples_framework.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/dw_samples_framework.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
