testMenu = {
    changeSceneButton = {
        Transform = {
            position = "0.4, 0.3, 0",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        Enabled = "true",
        Button = {
            overlayName = "ChangeScene",
            imageName = "DefaultButton",
            hoverImageName = "TestButtonAmongus",
            pressedImageName = "ButtonApretado",
            onClick = "changeScene"
        }
    },
    optionsButton = {
        Transform = {
            position = "0.4, 0.5, 0",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        Enabled = "true",
        Button = {
            overlayName = "Options",
            imageName = "DefaultButton",
            hoverImageName = "TestButtonAmongus",
            pressedImageName = "ButtonApretado",
            onClick = "goToOptions"
        }
    },
    exitButton = {
        Transform = {
            position = "0.4, 0.7, 0",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        Enabled = "true",
        Button = {
            overlayName = "Exit",
            imageName = "DefaultButton",
            hoverImageName = "TestButtonAmongus",
            pressedImageName = "ButtonApretado",
            onClick = "exitGame"
        }
    },
    fullScreenButton = {
        Transform = {
            position = "0.4, 0.1, 0",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        Enabled = "true",
        Button = {
            overlayName = "FullScreen",
            imageName = "DefaultButton",
            hoverImageName = "TestButtonAmongus",
            pressedImageName = "ButtonApretado",
            onClick = "fullScreen"
        }
    },
    focus = {
        Transform = {
            position = "0, 0, 200",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        Enabled = "true",
        Focus = {
            overlayName = "FocusElement",
            imageName = "SelectorFoco"
        }
    },
}

function changeScene()
    local sceneMan = SceneManager.getSceneMan();
    sceneMan:changeScene("map");
end

function goToOptions()
    local sceneMan = SceneManager.getSceneMan();
    sceneMan:changeScene("options");
end

function exitGame()
    local renderMan = RenderManager.getRenderMan();
    renderMan:exitGame();
end

function fullScreen()
    local renderMan = RenderManager.getRenderMan();
    renderMan:fullScreen();
end

testMenu_entities = { "changeSceneButton", "optionsButton", "exitButton", "fullScreenButton", "focus"}