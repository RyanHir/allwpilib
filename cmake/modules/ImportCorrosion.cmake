include(FetchContent)

macro(wpilib_import_corrosion)
    FetchContent_Declare(
        Corrosion
        GIT_REPOSITORY https://github.com/AndrewGaspar/corrosion.git
        GIT_TAG origin/master
    )

    FetchContent_MakeAvailable(Corrosion)
endmacro()