//#include "SystemsRegistration.h"
//#include "SystemsManager.h"
//#include "Game/ManagersProvider.h"
//
//#include "Systems/MovementSystem.h"
//#include "Systems/RotationSystem.h"
//#include "Systems/CollisionSystem.h"
//#include "Systems/DamageSystem.h"
//#include "Systems/PlayerInputSystem.h"
//#include "Systems/CameraFollowSystem.h"
//#include "Systems/IntertiaSystem.h"
//#include "Systems/BulletSystem.h"
//#include "Systems/CleanupSystem.h"
//#include "Systems/CameraSystem.h"
//#include "Systems/SpriteFrameAnimationSystem.h"
//#include "Systems/PhysicsBox2DSystem.h"
//
//#include "Systems/Editor/EditorSystem.h"
//
//#include "Systems/SDLSystems/SDLTilemapSystem.h"
//#include "Systems/SDLSystems/SDLInputSystem.h"
//#include "Systems/SDLSystems/SDLAnimatedDirectionSpriteUpdateSystem.h"
//
//#include "Systems/SDLSystems/SDLSpriteRenderSystem.h"
//#include "Systems/SDLSystems/SDLAnimatedSpriteUpdateSystem.h"
//#include "Systems/SDLSystems/SDLAnimatedSpriteRenderSystem.h"
//#include "Systems/SDLSystems/SDLBoundingBoxDebugSystem.h"
//
//#include "Systems/OpenGLSystems/OpenGLSpriteRenderSystem.h"
//#include "Systems/OpenGLSystems/OpenGLGridRenderSystem.h"
//
//namespace shen
//{
//    void RegisterSystems()
//    {
//        if (auto manager = ManagersProvider::Instance().GetSystemsManager())
//        {
//            manager->RegisterSystem<SDLInputSystem>();
//            manager->RegisterSystem<CameraSystem>();
//            manager->RegisterSystem<SpriteFrameAnimationSystem>();
//            manager->RegisterSystem<PlayerInputSystem>();
//            manager->RegisterSystem<PhysicsBox2DSystem>();
//            manager->RegisterSystem<MovementSystem>();
//            manager->RegisterSystem<RotationSystem>();
//            manager->RegisterSystem<IntertiaSystem>();
//            
//            /*
//            manager->RegisterSystem<BulletSystem>();
//            manager->RegisterSystem<CollisionSystem>();
//            manager->RegisterSystem<DamageSystem>();
//            manager->RegisterSystem<SDLAnimatedSpriteUpdateSystem>();
//            manager->RegisterSystem<SDLAnimatedDirectionSpriteUpdateSystem>();
//            manager->RegisterSystem<CameraFollowSystem>();
//            manager->RegisterSystem<CleanupSystem>();
//
//            manager->RegisterRenderSystem<SDLTilemapSystem>();
//            manager->RegisterRenderSystem<SDLSpriteRenderSystem>();
//            manager->RegisterRenderSystem<SDLAnimatedSpriteRenderSystem>();
//            manager->RegisterRenderSystem<SDLBoundingBoxDebugSystem>();*/
//
//            manager->RegisterRenderSystem<OpenGLGridRenderSystem>();
//            manager->RegisterRenderSystem<OpenGLSpriteRenderSystem>();
//            manager->RegisterSystem<EditorSystem>();
//        }
//    }
//}
