include_guard()

################################################################################
# Compile defintions for Windows
################################################################################

target_compile_definitions ("${PROJECT_NAME}-base"
  INTERFACE
    # Use Unicode character set
    $<$<PLATFORM_ID:Windows>:UNICODE>
    $<$<PLATFORM_ID:Windows>:_UNICODE>
    # Enable stricter type declarations and usage
    $<$<PLATFORM_ID:Windows>:STRICT>
    ############################################################################
    # Exclude APIs from "Windows.h" for faster builds
    #   1. Define WIN32_LEAN_AND_MEAN to exclude APIs such as Cryptography, DDE,
    #      RPC, Shell, and Windows Sockets.
    #   2. Define one or more of the NOapi symbols to exclude the API. For
    #      example, NOCOMM excludes the serial communication API. For a list of
    #      support NOapi symbols, see Windows.h.
    ############################################################################
    # Cryptography, DDE, RPC, Shell, and Windows Sockets
    $<$<PLATFORM_ID:Windows>:WIN32_LEAN_AND_MEAN>
    # *  NOGDICAPMASKS     - CC_*, LC_*, PC_*, CP_*, TC_*, RC_
    $<$<PLATFORM_ID:Windows>:NOGDICAPMASKS>
    # # *  NOVIRTUALKEYCODES - VK_*
    # $<$<PLATFORM_ID:Windows>:NOVIRTUALKEYCODES>
    # # *  NOWINMESSAGES     - WM_*, EM_*, LB_*, CB_*
    # $<$<PLATFORM_ID:Windows>:NOWINMESSAGES>
    # # *  NOWINSTYLES       - WS_*, CS_*, ES_*, LBS_*, SBS_*, CBS_*
    # $<$<PLATFORM_ID:Windows>:NOWINSTYLES>
    # *  NOSYSMETRICS      - SM_*
    $<$<PLATFORM_ID:Windows>:NOSYSMETRICS>
    # *  NOMENUS           - MF_*
    $<$<PLATFORM_ID:Windows>:NOMENUS>
    # *  NOICONS           - IDI_*
    $<$<PLATFORM_ID:Windows>:NOICONS>
    # *  NOKEYSTATES       - MK_*
    $<$<PLATFORM_ID:Windows>:NOKEYSTATES>
    # *  NOSYSCOMMANDS     - SC_*
    $<$<PLATFORM_ID:Windows>:NOSYSCOMMANDS>
    # *  NORASTEROPS       - Binary and Tertiary raster ops
    $<$<PLATFORM_ID:Windows>:NORASTEROPS>
    # # *  NOSHOWWINDOW      - SW_*
    # $<$<PLATFORM_ID:Windows>:NOSHOWWINDOW>
    # *  OEMRESOURCE       - OEM Resource values
    $<$<PLATFORM_ID:Windows>:OEMRESOURCE>
    # *  NOATOM            - Atom Manager routines
    $<$<PLATFORM_ID:Windows>:NOATOM>
    # *  NOCLIPBOARD       - Clipboard routines
    $<$<PLATFORM_ID:Windows>:NOCLIPBOARD>
    # # *  NOCOLOR           - Screen colors
    # $<$<PLATFORM_ID:Windows>:NOCOLOR>
    # *  NOCTLMGR          - Control and Dialog routines
    $<$<PLATFORM_ID:Windows>:NOCTLMGR>
    # *  NODRAWTEXT        - DrawText() and DT_*
    $<$<PLATFORM_ID:Windows>:NODRAWTEXT>
    # # *  NOGDI             - All GDI defines and routines
    # $<$<PLATFORM_ID:Windows>:NOGDI>
    # *  NOKERNEL          - All KERNEL defines and routines
    $<$<PLATFORM_ID:Windows>:NOKERNEL>
    # # *  NOUSER            - All USER defines and routines
    # $<$<PLATFORM_ID:Windows>:NOUSER>
    # *  NONLS             - All NLS defines and routines
    $<$<PLATFORM_ID:Windows>:NONLS>
    # # *  NOMB              - MB_* and MessageBox()
    # $<$<PLATFORM_ID:Windows>:NOMB>
    # *  NOMEMMGR          - GMEM_*, LMEM_*, GHND, LHND, associated routines
    $<$<PLATFORM_ID:Windows>:NOMEMMGR>
    # *  NOMETAFILE        - typedef METAFILEPICT
    $<$<PLATFORM_ID:Windows>:NOMETAFILE>
    # *  NOMINMAX          - Macros min(a,b) and max(a,b)
    $<$<PLATFORM_ID:Windows>:NOMINMAX>
    # # *  NOMSG             - typedef MSG and associated routines
    # $<$<PLATFORM_ID:Windows>:NOMSG>
    # *  NOOPENFILE        - OpenFile(), OemToAnsi, AnsiToOem, and OF_*
    $<$<PLATFORM_ID:Windows>:NOOPENFILE>
    # *  NOSCROLL          - SB_* and scrolling routines
    $<$<PLATFORM_ID:Windows>:NOSCROLL>
    # *  NOSERVICE         - All Service Controller routines, SERVICE_ equates, etc.
    $<$<PLATFORM_ID:Windows>:NOSERVICE>
    # *  NOSOUND           - Sound driver routines
    $<$<PLATFORM_ID:Windows>:NOSOUND>
    # *  NOTEXTMETRIC      - typedef TEXTMETRIC and associated routines
    $<$<PLATFORM_ID:Windows>:NOTEXTMETRIC>
    # *  NOWH              - SetWindowsHook and WH_*
    $<$<PLATFORM_ID:Windows>:NOWH>
    # *  NOWINOFFSETS      - GWL_*, GCL_*, associated routines
    $<$<PLATFORM_ID:Windows>:NOWINOFFSETS>
    # *  NOCOMM            - COMM driver routines
    $<$<PLATFORM_ID:Windows>:NOCOMM>
    # *  NOKANJI           - Kanji support stuff.
    $<$<PLATFORM_ID:Windows>:NOKANJI>
    # *  NOHELP            - Help engine interface.
    $<$<PLATFORM_ID:Windows>:NOHELP>
    # *  NOPROFILER        - Profiler interface.
    $<$<PLATFORM_ID:Windows>:NOPROFILER>
    # *  NODEFERWINDOWPOS  - DeferWindowPos routines
    $<$<PLATFORM_ID:Windows>:NODEFERWINDOWPOS>
    # *  NOMCX             - Modem Configuration Extensions
    $<$<PLATFORM_ID:Windows>:NOMCX>
)
