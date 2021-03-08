function [tc, results] = catkin_toolchain()
%CATKIN_TOOLCHAIN Toolchain definition file

% Copyright 2014-2017 The MathWorks, Inc.

toolchain.Platforms  = {computer('arch')};
toolchain.Versions   = {'1.0'};
toolchain.Artifacts  = {'gmake'};
toolchain.FuncHandle = str2func('getToolchainInfoFor');
toolchain.ExtraFuncArgs = {};

[tc, results] = coder.make.internal.generateToolchainInfoObjects(mfilename, toolchain);
end

function tc = getToolchainInfoFor(platform, version, artifact, varargin)
% Toolchain Information

tc = coder.make.ToolchainInfo('BuildArtifact', 'gmake makefile', 'SupportedLanguages', {'Asm/C/C++'});
tc.Name = coder.make.internal.formToolchainName('Catkin', ...
    platform, version, artifact);
tc.Platform = platform;
tc.setBuilderApplication(platform);

% MATLAB setup
%tc.MATLABSetup = 'robotic.internal.addCompilerPath();';

% Toolchain's attribute
tc.addAttribute('TransformPathsWithSpaces');
tc.addAttribute('SupportsUNCPaths',     false);
tc.addAttribute('SupportsDoubleQuotes', false);


% ------------------------------
% Make
% ------------------------------
make = tc.BuilderApplication();
make.IncludeFiles = {'codertarget_assembly_flags.mk', '../codertarget_assembly_flags.mk'};
make.setPath('');
make.setCommand('echo');

% Add macros
%tc.addIntrinsicMacros({'TARGET_LOAD_CMD_ARGS'});
%tc.addIntrinsicMacros({'TARGET_PKG_INSTALLDIR'});
%tc.addIntrinsicMacros({'LINARO_TOOLCHAIN_4_8'});

if ispc
    tc.addMacro('SHELL', '%SystemRoot%/system32/cmd.exe');
end
tc.addMacro('CCOUTPUTFLAG', '--output_file=');
tc.addMacro('LDOUTPUTFLAG', '--output_file=');
% tc.addMacro('CPFLAGS', '-O binary');

% Assembler
assembler = tc.getBuildTool('Assembler');
assembler.setName(['Catkin', version, ' Assembler']);
%assembler.setPath('$(LINARO_TOOLCHAIN_4_8)');
assembler.setCommand('echo as');
assembler.setDirective('IncludeSearchPath', '-I');
assembler.setDirective('PreprocessorDefine', '-D');
assembler.setDirective('OutputFlag', '-o');
assembler.setDirective('Debug', '-g');
assembler.DerivedFileExtensions = {'Object'};
assembler.setFileExtension('Source','.s');
assembler.setFileExtension('Object', '.s.o');

% Compiler
compiler = tc.getBuildTool('C Compiler');
compiler.setName(['Catkin', version, ' C Compiler']);
%compiler.setPath('$(LINARO_TOOLCHAIN_4_8)');
compiler.setCommand('echo gcc');
compiler.setDirective('IncludeSearchPath', '-I');
compiler.setDirective('PreprocessorDefine', '-D');
compiler.setDirective('OutputFlag', '-o');
compiler.setDirective('Debug', '-g');
compiler.setFileExtension('Source', '.c');
compiler.setFileExtension('Header', '.h');
compiler.setFileExtension('Object', '.c.o');

% C++ compiler
cppcompiler = tc.getBuildTool('C++ Compiler');
cppcompiler.setName(['Catkin', version, ' C++ Compiler']);
%cppcompiler.setPath('$(LINARO_TOOLCHAIN_4_8)');
cppcompiler.setCommand('echo g++');
cppcompiler.setDirective('IncludeSearchPath', '-I');
cppcompiler.setDirective('PreprocessorDefine', '-D');
cppcompiler.setDirective('OutputFlag', '-o');
cppcompiler.setDirective('Debug', '-g');
cppcompiler.setFileExtension('Source', '.cpp');
cppcompiler.setFileExtension('Header', '.hpp');
cppcompiler.setFileExtension('Object', '.cpp.o');

% Linker
linker = tc.getBuildTool('Linker');
linker.setName(['Catkin', version, ' Linker']);
%linker.setPath('$(LINARO_TOOLCHAIN_4_8)');
linker.setCommand('echo gcc');
linker.setDirective('Library', '-l');
linker.setDirective('LibrarySearchPath', '-L');
linker.setDirective('OutputFlag', '-o');
linker.setDirective('Debug', '-g');
linker.setFileExtension('Executable', '.elf');
linker.setFileExtension('Shared Library', '.so');
linker.Libraries = {'-lm'};

% C++ Linker
cpplinker = tc.getBuildTool('C++ Linker');
cpplinker.setName(['Catkin', version, ' C++ Linker']);
%cpplinker.setPath('$(LINARO_TOOLCHAIN_4_8)');
cpplinker.setCommand('echo gcc');
cpplinker.setDirective('Library', '-l');
cpplinker.setDirective('LibrarySearchPath', '-L');
cpplinker.setDirective('OutputFlag', '-o');
cpplinker.setDirective('Debug', '-g');
cpplinker.setFileExtension('Executable', '');
cpplinker.setFileExtension('Shared Library', '.so');
cpplinker.Libraries = {'-lm'};

% Archiver
archiver = tc.getBuildTool('Archiver');
%archiver.setPath('$(LINARO_TOOLCHAIN_4_8)');
archiver.setName(['Catkin', version, ' Archiver']);
archiver.setCommand('echo ar');
archiver.setDirective('OutputFlag', '');
archiver.setFileExtension('Static Library', '.lib');

% --------------------------------------------
% BUILD CONFIGURATIONS
% --------------------------------------------
optimsOffOpts = {'-O0'};
optimsOnOpts = {'-O2'};
cCompilerOpts = {''};
archiverOpts = {'-r'};

compilerOpts = {...
    '-c',...
    };

linkerOpts = {};

assemblerOpts = compilerOpts;

% Get the debug flag per build tool
debugFlag.CCompiler   = '-g -D"_DEBUG"';
debugFlag.Linker      = '-g';
debugFlag.Archiver    = '-g';

cfg = tc.getBuildConfiguration('Faster Builds');
cfg.setOption('Assembler',  horzcat(cCompilerOpts, assemblerOpts, '$(ASFLAGS_ADDITIONAL)', '$(INCLUDES)'));
cfg.setOption('C Compiler', horzcat(cCompilerOpts, compilerOpts, optimsOffOpts));
cfg.setOption('Linker',     linkerOpts);
cfg.setOption('Archiver',   archiverOpts);

cfg = tc.getBuildConfiguration('Faster Runs');
cfg.setOption('Assembler',  horzcat(cCompilerOpts, assemblerOpts, '$(ASFLAGS_ADDITIONAL)', '$(INCLUDES)'));
cfg.setOption('C Compiler', horzcat(cCompilerOpts, compilerOpts, optimsOnOpts));
cfg.setOption('Linker',     linkerOpts);
cfg.setOption('Archiver',   archiverOpts);

cfg = tc.getBuildConfiguration('Debug');
cfg.setOption('Assembler',  horzcat(cCompilerOpts, assemblerOpts, '$(ASFLAGS_ADDITIONAL)', '$(INCLUDES)', debugFlag.CCompiler));
cfg.setOption('C Compiler', horzcat(cCompilerOpts, compilerOpts, optimsOffOpts, debugFlag.CCompiler));
cfg.setOption('Linker',     horzcat(linkerOpts, debugFlag.Linker));
cfg.setOption('Archiver',   horzcat(archiverOpts, debugFlag.Archiver));

tc.setBuildConfigurationOption('all', 'Download',  '');
tc.setBuildConfigurationOption('all', 'Execute',   '');
tc.setBuildConfigurationOption('all', 'Make Tool', '"### Successfully generated all binary outputs."');

end
