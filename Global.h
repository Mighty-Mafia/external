#pragma 
#include <memory>
#include <Driver/communication.h>
#include <Render/Render.h>
#include <SDK/Classes/DataModel/DataModel.h>
#include <SDK/Classes/VisualEngine/VisualEngine.h>

inline std::unique_ptr<communication> Comms = std::make_unique<communication>();
inline std::unique_ptr<Render> render;

inline std::unique_ptr<RBX::DataModel> dataModel;
inline std::unique_ptr<RBX::VisualEngine> visualEngine;
