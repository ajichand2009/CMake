/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#pragma once

#include "cmConfigure.h" // IWYU pragma: keep

#include <iosfwd>
#include <set>
#include <string>

#include "cmExportInstallFileGenerator.h"
#include "cmStateTypes.h"

class cmGeneratorTarget;
class cmInstallExportGenerator;

/** \class cmExportInstallAndroidMKGenerator
 * \brief Generate a file exporting targets from an install tree.
 *
 * cmExportInstallAndroidMKGenerator generates files exporting targets from
 * install an installation tree.  The files are placed in a temporary
 * location for installation by cmInstallExportGenerator.  The file format
 * is for the ndk build system and is a makefile fragment specifying prebuilt
 * libraries to the ndk build system.
 *
 * This is used to implement the INSTALL(EXPORT_ANDROID_MK) command.
 */
class cmExportInstallAndroidMKGenerator : public cmExportInstallFileGenerator
{
public:
  /** Construct with the export installer that will install the
      files.  */
  cmExportInstallAndroidMKGenerator(cmInstallExportGenerator* iegen);

protected:
  // Implement virtual methods from the superclass.
  void GeneratePolicyHeaderCode(std::ostream&) override {}
  void GeneratePolicyFooterCode(std::ostream&) override {}
  void GenerateImportHeaderCode(std::ostream& os,
                                std::string const& config = "") override;
  void GenerateImportFooterCode(std::ostream& os) override;
  void GenerateImportTargetCode(
    std::ostream& os, cmGeneratorTarget const* target,
    cmStateEnums::TargetType /*targetType*/) override;
  void GenerateExpectedTargetsCode(
    std::ostream& os, std::string const& expectedTargets) override;
  void GenerateImportPropertyCode(
    std::ostream& os, std::string const& config, std::string const& suffix,
    cmGeneratorTarget const* target, ImportPropertyMap const& properties,
    std::string const& importedXcFrameworkLocation) override;
  void GenerateMissingTargetsCheckCode(std::ostream& os) override;
  void GenerateFindDependencyCalls(std::ostream&) override {}
  void GenerateInterfaceProperties(
    cmGeneratorTarget const* target, std::ostream& os,
    ImportPropertyMap const& properties) override;
  void GenerateImportPrefix(std::ostream& os) override;
  void LoadConfigFiles(std::ostream&) override;
  void CleanupTemporaryVariables(std::ostream&) override;
  void GenerateImportedFileCheckLoop(std::ostream& os) override;
  void GenerateImportedFileChecksCode(
    std::ostream& os, cmGeneratorTarget* target,
    ImportPropertyMap const& properties,
    std::set<std::string> const& importedLocations,
    std::string const& importedXcFrameworkLocation) override;
  bool GenerateImportFileConfig(std::string const& config) override;
};
