idf_component_register(
  SRCS "main.c" "./main.c" "../../../../src/ADS1110.c" "../../../../port/ESP32-IDF/ADS1110_platform.c"
  INCLUDE_DIRS "../../../../src/include" "../../../../port/ESP32-IDF"
  )