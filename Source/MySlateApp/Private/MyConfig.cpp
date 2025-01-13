#include "CoreMinimal.h"
#include "FileHelper.h"
#include "Paths.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"

#include "MyConfig.h"
#include "Log.h"

class FMyConfigLoader
{
public:
    static TSharedPtr<FMyConfig> Load(const FString &ConfigPath);
    static bool Save(const FString &ConfigPath, const FMyConfig &Config);
};

TSharedPtr<FMyConfig> FMyConfigLoader::Load(const FString &ConfigPath)
{
    TSharedPtr<FMyConfig> Config = MakeShared<FMyConfig>();

    FString Content;
    if (!FFileHelper::LoadFileToString(Content, *ConfigPath))
    {
        ERR("Failed to load config file: %s", *ConfigPath);
        return Config;
    }    
    
    TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Content);
    TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
    if (!FJsonSerializer::Deserialize(JsonReader, JsonObject))
    {
        ERR("Failed to deserialize config file: %s", *ConfigPath);
        return Config;
    }

    if (!FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), FMyConfig::StaticStruct(), Config.Get()))
    {
        ERR("Failed to deserialize config file: %s", *ConfigPath);
        return Config;
    }
    
    LOG("Config file loaded: %s", *ConfigPath);
    return Config;
}

bool FMyConfigLoader::Save(const FString &ConfigPath, const FMyConfig &Config)
{
    TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();
    if (FJsonObjectConverter::UStructToJsonObject(FMyConfig::StaticStruct(), &Config, JsonObject))
    {
        FString JsonString;
        TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);
        if (FJsonSerializer::Serialize(JsonObject, JsonWriter))
        {
            if (TUniquePtr<FArchive> FileWriter = TUniquePtr<FArchive>(IFileManager::Get().CreateFileWriter(*ConfigPath)))
            {
                FileWriter->Serialize(TCHAR_TO_ANSI(*JsonString), JsonString.Len());
                LOG("Config file saved: %s", *ConfigPath);
                return true;
            }
            else
            {
                ERR("Failed to open config file for writing: %s", *ConfigPath);
            }
        }
        else
        {
            ERR("Failed to serialize config file: %s", *ConfigPath);
        }
    }
    else
    {
        ERR("Failed to serialize config file: %s", *ConfigPath);
    }

    return false;
}

namespace
{
    FString GetConfigPath()
    {
        return FPaths::Combine(FPaths::ProjectUserDir(), TEXT("MyConfig.json"));
    }
}

FMyConfigGetter *FMyConfigGetter::Instance = nullptr;

FMyConfigGetter& FMyConfigGetter::Get()
{
    if (!Instance)
    {
        Instance = new FMyConfigGetter();
    }
    
    return *Instance;
}

void FMyConfigGetter::Destroy()
{
    if (Instance)
    {
        delete Instance;
        Instance = nullptr;
    }
}

TSharedPtr<FMyConfig> FMyConfigGetter::GetConfig()
{
    if (!Config.IsValid())
    {
        Config = FMyConfigLoader::Load(GetConfigPath());
    }

    return Config;
}

bool FMyConfigGetter::Save()
{
    if (Config.IsValid())
    {
        return FMyConfigLoader::Save(GetConfigPath(), *Config);
    }

    return false;
}
