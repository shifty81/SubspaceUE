// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SubspaceUE : ModuleRules
{
	public SubspaceUE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"EnhancedInput",
			"UMG",
			"Slate",
			"SlateCore",
			"AIModule",
			"NavigationSystem",
			"GameplayTasks",
			"ProceduralMeshComponent",
			"GeometryScriptingCore",
			"OnlineSubsystem",
			"OnlineSubsystemUtils"
		});

		PrivateDependencyModuleNames.AddRange(new string[] 
		{
			"Sockets",
			"Networking",
			"Json",
			"JsonUtilities"
		});

		// For procedural generation
		PublicIncludePaths.AddRange(new string[] 
		{
			"SubspaceUE/Public"
		});

		PrivateIncludePaths.AddRange(new string[] 
		{
			"SubspaceUE/Private"
		});
	}
}
