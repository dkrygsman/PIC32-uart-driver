#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Lab_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Lab_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=C:/Users/danie/OneDrive/Desktop/ECE121_LABS/dkrygsma/projects/Lab1/Lab_1.X/Uart.c C:/Users/danie/OneDrive/Desktop/ECE121_files/src/BOARD.c C:/Users/danie/OneDrive/Desktop/ECE121_LABS/dkrygsma/projects/Lab1/Lab_1.X/buffer.c C:/Users/danie/OneDrive/Desktop/ECE121_LABS/dkrygsma/projects/Lab1/Lab_1.X/Protocol2.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/343533582/Uart.o ${OBJECTDIR}/_ext/1463773791/BOARD.o ${OBJECTDIR}/_ext/343533582/buffer.o ${OBJECTDIR}/_ext/343533582/Protocol2.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/343533582/Uart.o.d ${OBJECTDIR}/_ext/1463773791/BOARD.o.d ${OBJECTDIR}/_ext/343533582/buffer.o.d ${OBJECTDIR}/_ext/343533582/Protocol2.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/343533582/Uart.o ${OBJECTDIR}/_ext/1463773791/BOARD.o ${OBJECTDIR}/_ext/343533582/buffer.o ${OBJECTDIR}/_ext/343533582/Protocol2.o

# Source Files
SOURCEFILES=C:/Users/danie/OneDrive/Desktop/ECE121_LABS/dkrygsma/projects/Lab1/Lab_1.X/Uart.c C:/Users/danie/OneDrive/Desktop/ECE121_files/src/BOARD.c C:/Users/danie/OneDrive/Desktop/ECE121_LABS/dkrygsma/projects/Lab1/Lab_1.X/buffer.c C:/Users/danie/OneDrive/Desktop/ECE121_LABS/dkrygsma/projects/Lab1/Lab_1.X/Protocol2.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Lab_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX340F512H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/343533582/Uart.o: C:/Users/danie/OneDrive/Desktop/ECE121_LABS/dkrygsma/projects/Lab1/Lab_1.X/Uart.c  .generated_files/flags/default/43476a8a045a3f3a0e946812768a3c28e0acbc90 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/343533582" 
	@${RM} ${OBJECTDIR}/_ext/343533582/Uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/343533582/Uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../../../ECE121_files/include" -MP -MMD -MF "${OBJECTDIR}/_ext/343533582/Uart.o.d" -o ${OBJECTDIR}/_ext/343533582/Uart.o C:/Users/danie/OneDrive/Desktop/ECE121_LABS/dkrygsma/projects/Lab1/Lab_1.X/Uart.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1463773791/BOARD.o: C:/Users/danie/OneDrive/Desktop/ECE121_files/src/BOARD.c  .generated_files/flags/default/48cd752619d8240ab809e822edb0652be3eb8ce4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1463773791" 
	@${RM} ${OBJECTDIR}/_ext/1463773791/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1463773791/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../../../ECE121_files/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1463773791/BOARD.o.d" -o ${OBJECTDIR}/_ext/1463773791/BOARD.o C:/Users/danie/OneDrive/Desktop/ECE121_files/src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/343533582/buffer.o: C:/Users/danie/OneDrive/Desktop/ECE121_LABS/dkrygsma/projects/Lab1/Lab_1.X/buffer.c  .generated_files/flags/default/1c59600167d1797cc19f39fe8a2fc79b41ed8cd5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/343533582" 
	@${RM} ${OBJECTDIR}/_ext/343533582/buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/343533582/buffer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../../../ECE121_files/include" -MP -MMD -MF "${OBJECTDIR}/_ext/343533582/buffer.o.d" -o ${OBJECTDIR}/_ext/343533582/buffer.o C:/Users/danie/OneDrive/Desktop/ECE121_LABS/dkrygsma/projects/Lab1/Lab_1.X/buffer.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/343533582/Protocol2.o: C:/Users/danie/OneDrive/Desktop/ECE121_LABS/dkrygsma/projects/Lab1/Lab_1.X/Protocol2.c  .generated_files/flags/default/e7d16684fe49ee438c8897fa83f22194c45451b2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/343533582" 
	@${RM} ${OBJECTDIR}/_ext/343533582/Protocol2.o.d 
	@${RM} ${OBJECTDIR}/_ext/343533582/Protocol2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../../../ECE121_files/include" -MP -MMD -MF "${OBJECTDIR}/_ext/343533582/Protocol2.o.d" -o ${OBJECTDIR}/_ext/343533582/Protocol2.o C:/Users/danie/OneDrive/Desktop/ECE121_LABS/dkrygsma/projects/Lab1/Lab_1.X/Protocol2.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/343533582/Uart.o: C:/Users/danie/OneDrive/Desktop/ECE121_LABS/dkrygsma/projects/Lab1/Lab_1.X/Uart.c  .generated_files/flags/default/aa91b70143eaccfaf61444be6b2a02dd0b6d3854 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/343533582" 
	@${RM} ${OBJECTDIR}/_ext/343533582/Uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/343533582/Uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../../../ECE121_files/include" -MP -MMD -MF "${OBJECTDIR}/_ext/343533582/Uart.o.d" -o ${OBJECTDIR}/_ext/343533582/Uart.o C:/Users/danie/OneDrive/Desktop/ECE121_LABS/dkrygsma/projects/Lab1/Lab_1.X/Uart.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1463773791/BOARD.o: C:/Users/danie/OneDrive/Desktop/ECE121_files/src/BOARD.c  .generated_files/flags/default/54aa00898f7131bca15739ae2f6c3205fa7e1782 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1463773791" 
	@${RM} ${OBJECTDIR}/_ext/1463773791/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1463773791/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../../../ECE121_files/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1463773791/BOARD.o.d" -o ${OBJECTDIR}/_ext/1463773791/BOARD.o C:/Users/danie/OneDrive/Desktop/ECE121_files/src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/343533582/buffer.o: C:/Users/danie/OneDrive/Desktop/ECE121_LABS/dkrygsma/projects/Lab1/Lab_1.X/buffer.c  .generated_files/flags/default/c28260d8b05e6c7043d120f871661c8bb6e0df48 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/343533582" 
	@${RM} ${OBJECTDIR}/_ext/343533582/buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/343533582/buffer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../../../ECE121_files/include" -MP -MMD -MF "${OBJECTDIR}/_ext/343533582/buffer.o.d" -o ${OBJECTDIR}/_ext/343533582/buffer.o C:/Users/danie/OneDrive/Desktop/ECE121_LABS/dkrygsma/projects/Lab1/Lab_1.X/buffer.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/343533582/Protocol2.o: C:/Users/danie/OneDrive/Desktop/ECE121_LABS/dkrygsma/projects/Lab1/Lab_1.X/Protocol2.c  .generated_files/flags/default/1ac6c3fc535c97b1deeda4a348775a1ea88a36b4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/343533582" 
	@${RM} ${OBJECTDIR}/_ext/343533582/Protocol2.o.d 
	@${RM} ${OBJECTDIR}/_ext/343533582/Protocol2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../../../ECE121_files/include" -MP -MMD -MF "${OBJECTDIR}/_ext/343533582/Protocol2.o.d" -o ${OBJECTDIR}/_ext/343533582/Protocol2.o C:/Users/danie/OneDrive/Desktop/ECE121_LABS/dkrygsma/projects/Lab1/Lab_1.X/Protocol2.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Lab_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Lab_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/Lab_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Lab_1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/Lab_1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
