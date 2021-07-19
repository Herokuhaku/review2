<?xml version="1.0" encoding="UTF-8"?>
<objectList name = "Player">
	<actionNode name="LR">
			<attach name="CheckKey" state = "CntKey" key="Right">
			<attach name ="ColisionCheck" speed="5" width="32">
			<attach name="SetAnime" state = "right"/>
			<attach name="Move" x="5" y = "0"/>
			</attach
	>	</attach>
			<attach name="CheckKey" state = "CntKey" key="Left">
			<attach name ="ColisionCheck" speed="-5" width="-32">
			<attach name="SetAnime" state = "left"/>
			<attach name="Move" x="-5" y = "0"/>
		</attach>
	</attach>
	</actionNode>
	<actionNode name="Jump">
		<attach name ="CheckKey" key="Space">
			<attach name="Jump" time="0.50" />
		</attach>
	</actionNode>
	<actionNode name="Command">
		<attach name ="CheckCommand" commandname="beam" key="btn1" gracetime="0.2">
			<attach name="Command" key="right" gracetime="0.1" check="continue">
				<attach name="Command" key="left"gracetime="0.1" check="continue">
					<attach name="Command" commandname = "beam" check="clear">
					</attach>
				</attach>
			</attach>
		</attach>
	</actionNode>
</objectList>
