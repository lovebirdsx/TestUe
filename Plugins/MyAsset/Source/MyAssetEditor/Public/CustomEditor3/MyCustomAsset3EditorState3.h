#pragma once

class UMyCustomAsset3;

class IMyCustomAsset3EditorState3
{
public:
    virtual UMyCustomAsset3* GetAsset() = 0;
    virtual UEdGraph* GetGraph() = 0;

    virtual ~IMyCustomAsset3EditorState3() = default;
};
