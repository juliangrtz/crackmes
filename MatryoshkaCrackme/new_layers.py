import os
import shutil
import uuid

# Configuration
number_of_layers = 10  # Number of layers to generate

# Templates
csproj_template = r"""<?xml version="1.0" encoding="utf-8"?>
<Project ToolsVersion="15.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <Import Project="$(MSBuildExtensionsPath)\$(MSBuildToolsVersion)\Microsoft.Common.props" Condition="Exists('$(MSBuildExtensionsPath)\$(MSBuildToolsVersion)\Microsoft.Common.props')" />
  <PropertyGroup>
    <Configuration Condition=" '$(Configuration)' == '' ">Debug</Configuration>
    <Platform Condition=" '$(Platform)' == '' ">AnyCPU</Platform>
    <ProjectGuid>{GUID}</ProjectGuid>
    <OutputType>Library</OutputType>
    <RootNamespace>Layer{X}</RootNamespace>
    <AssemblyName>Layer{X}</AssemblyName>
    <TargetFrameworkVersion>v4.7.2</TargetFrameworkVersion>
    <FileAlignment>512</FileAlignment>
    <Deterministic>true</Deterministic>
  </PropertyGroup>
  <PropertyGroup Condition=" '$(Configuration)|$(Platform)' == 'Debug|AnyCPU' ">
    <DebugSymbols>true</DebugSymbols>
    <DebugType>full</DebugType>
    <Optimize>false</Optimize>
    <OutputPath>bin\\Debug\\</OutputPath>
    <DefineConstants>DEBUG;TRACE</DefineConstants>
    <ErrorReport>prompt</ErrorReport>
    <WarningLevel>4</WarningLevel>
  </PropertyGroup>
  <PropertyGroup Condition=" '$(Configuration)|$(Platform)' == 'Release|AnyCPU' ">
    <DebugType>pdbonly</DebugType>
    <Optimize>true</Optimize>
    <OutputPath>bin\\Release\\</OutputPath>
    <DefineConstants>TRACE</DefineConstants>
    <ErrorReport>prompt</ErrorReport>
    <WarningLevel>4</WarningLevel>
  </PropertyGroup>
  <ItemGroup>
    <Reference Include="System" />
    <Reference Include="System.Core" />
    <Reference Include="System.Xml.Linq" />
    <Reference Include="System.Data.DataSetExtensions" />
    <Reference Include="Microsoft.CSharp" />
    <Reference Include="System.Data" />
    <Reference Include="System.Net.Http" />
    <Reference Include="System.Xml" />
  </ItemGroup>
  <ItemGroup>
    <Compile Include="Layer{X}Checker.cs" />
    <Compile Include="Properties\\AssemblyInfo.cs" />
  </ItemGroup>
  <Import Project="$(MSBuildToolsPath)\\Microsoft.CSharp.targets" />
</Project>
"""

checker_cs_template = r"""using System;
using System.Linq;
using System.Reflection;

namespace Layer{X} {{
    public class Layer{X}Checker {{
        public static bool IsValid(string username, string licenseKey) {{
            var assembly = Assembly.Load(Resources.Layer{NEXT});
            var type = assembly.GetTypes().Where(t => t.Name.Equals("Layer{NEXT}Checker")).First();
            var isValidFunction = type.GetMethod("IsValid");
            return (bool)isValidFunction?.Invoke(null, new object[] {{ username, licenseKey }});
        }}
    }}
}}
"""

# Function to create new layer
def create_layer(layer_number):
    next_layer = layer_number + 1
    layer_folder = f"Layer{layer_number}"
    
    # Create the layer directory
    os.makedirs(layer_folder, exist_ok=True)
    
    # Create the csproj file
    project_guid = "{0}".format(str.upper(str(uuid.uuid4())))
    csproj_content = csproj_template.replace("{X}", str(layer_number)).replace("{GUID}", project_guid)
    with open(os.path.join(layer_folder, f"Layer{layer_number}.csproj"), "w", encoding='utf-8') as csproj_file:
        csproj_file.write(csproj_content)
    
    # Create the Checker.cs file
    checker_cs_content = checker_cs_template.replace("{X}", str(layer_number)).replace("{NEXT}", str(next_layer))
    with open(os.path.join(layer_folder, f"Layer{layer_number}Checker.cs"), "w", encoding='utf-8') as checker_file:
        checker_file.write(checker_cs_content)

    # Create the Properties folder with AssemblyInfo.cs
    properties_folder = os.path.join(layer_folder, "Properties")
    os.makedirs(properties_folder, exist_ok=True)
    shutil.copy("Layer0/Properties/AssemblyInfo.cs", properties_folder)

# Generate all layers
for i in range(1, number_of_layers + 1):
    create_layer(i)
    
# Update the solution file
sln_path = "MatryoshkaCrackme.sln"
with open(sln_path, "a") as sln_file:
    for i in range(1, number_of_layers + 1):
        sln_file.write(f'Project("{{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}}") = "Layer{i}", "Layer{i}\\Layer{i}.csproj", "{str.upper(str(uuid.uuid4()))}"\n')
        sln_file.write("EndProject\n")