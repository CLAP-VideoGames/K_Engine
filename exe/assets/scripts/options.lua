options = {
    sliderVolume = {
        Transform = {
            position = "600, 500, 60",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        Enabled = "true",
        Slider = {
            overlayName = "SliderVolumen",
            imageName = "DefaultButton",
            width = "500",
            onSliderClick = "setMasterVolume"
        }
    },
    popSceneButton = {
        Transform = {
            position = "1050, 200, 0",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        Enabled = "true",
        Button = {
            overlayName = "PopScene",
            imageName = "DefaultButton",
            hoverImageName = "TestButtonAmongus",
            pressedImageName = "ButtonApretado",
            onClick = "popScene"
        }
    },
}

function popScene()
    local sceneMan = SceneManager.getSceneMan();
    sceneMan:popScene("testMenu");
end

function setMasterVolume(volume)
    local audioMan = AudioManager.getAudioMan();
    audioMan:setMasterVolume(volume);
end

options_entities = {"sliderVolume", "popSceneButton"}