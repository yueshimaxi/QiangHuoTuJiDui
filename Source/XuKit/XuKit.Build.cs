// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class XuKit : ModuleRules
{
	public XuKit(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore",
			"UMG",
			"Json",
			"JsonUtilities",
			"CommonUI",
			"GameSettings",
			"GameSubtitles",
			"Slate",
			"SlateCore",
			"EnhancedInput",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"Navmesh",
			"NavigationSystem",
			"DlgSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem","OnlineSubsystemSteam", "Niagara" });


		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
