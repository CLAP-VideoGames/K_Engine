testMenu = {
    changeSceneButton = {
        Transform = {
            position = "750, 400, 0",
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
            position = "750, 600, 0",
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
            position = "750, 800, 0",
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
}

function changeScene()
    local sceneMan = SceneManager.getSceneManInstance();
    sceneMan:changeScene("map");
end

function goToOptions()
    local sceneMan = SceneManager.getSceneManInstance();
    sceneMan:changeScene("options");
end

function exitGame()

end

testMenu_entities = { "changeSceneButton", "optionsButton", "exitButton"}