<?xml version="1.0" encoding="UTF-8"?>
<objectList name = "Player">
	<actionNode name="LR">
			<attach name="CheckKey" state = "CntKey" key="Right">
			<attach name ="ColisionCheck" speed="8" width="32">
			<attach name="SetAnime" state = "right"/>
			<attach name="Move" x="8" y = "0"/>
			</attach
	>	</attach>
			<attach name="CheckKey" state = "CntKey" key="Left">
			<attach name ="ColisionCheck" speed="-8" width="-32">
			<attach name="SetAnime" state = "left"/>
			<attach name="Move" x="-8" y = "0"/>
		</attach>
	</attach>
	</actionNode>
	<actionNode name="Jump">
		<attach name ="CheckKey" key="Space">
			<attach name="Jump" time="0.1" />
		</attach>
	</actionNode>
	<actionNode name="Command">
		<attach name ="CheckCommand" commandname="beam" key="btn1" grace="1" >
			<attach name="Command" key="right" grace="10">
				<attach name="Command" key="left" grace="10">
				</attach>
			</attach>
		</attach>
	</actionNode >
</objectList>
