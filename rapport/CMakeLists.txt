
# Find dia and ps2pdf
include(FindPackageHandleStandardArgs)
find_program(DIA_EXECUTABLE NAMES dia)
find_package_handle_standard_args(Dia DEFAULT_MSG DIA_EXECUTABLE)
find_program(PS2PDF_EXECUTABLE NAMES ps2pdf)
find_package_handle_standard_args(Ps2Pdf DEFAULT_MSG PS2PDF_EXECUTABLE)

if(Ps2Pdf_FOUND AND Dia_FOUND)
  # Custom "rapport" target that creates pdf out of dia UML files
  add_custom_target(rapport)

  # Function that generate a pdf file out of a dia UML file.
  #
  # Arguments:
  #
  # name
  #   Name of the dia file
  #
  function(generate_dia_pdf name)
    set(dia_file "${PROJECT_SOURCE_DIR}/src/${name}.dia")
    set(pdf_dir "${PROJECT_SOURCE_DIR}/rapport/diapdf/")
    set(pdf_file "${name}.pdf")
    set(ps_file "${CMAKE_CURRENT_BINARY_DIR}/rapport_diapdf_${name}.ps")

    # Custom command that generate a pdf file from a dia UML file
    add_custom_command(
      OUTPUT ${pdf_file}
      COMMAND ${DIA_EXECUTABLE} -e ${ps_file} ${dia_file}
      COMMAND ${CMAKE_COMMAND} -E make_directory ${pdf_dir}
      COMMAND ${PS2PDF_EXECUTABLE} ${ps_file} ${pdf_dir}/${pdf_file}
      DEPENDS ${dia_file}
      )

    # Create a cmake intermediate target to generate a pdf out of a dia file
    add_custom_target(rapport-diapdf-${name} DEPENDS ${pdf_file})

    # Add the intermediate target as a dependency of the global cmake target
    # for rapport generation.
    add_dependencies(rapport rapport-diapdf-${name})
  endfunction()

  # Generate all pdf
  generate_dia_pdf(state)
  #generate_dia_pdf(render)
  #generate_dia_pdf(engine)
  #generate_dia_pdf(ai)
  #generate_dia_pdf(module)

else()
  message(WARNING "Dia or ps2pdf not found! Rapport generation not available!")
endif()

# vim: set sw=2 sts=2 et:
