<div class="loginForm">
	<fieldset id="login">
<?php
	echo $this->Form->create();
	echo $this->Form->input('username', array('label' => 'Nome de usuário'));
	echo $this->Form->input('password', array('label' => 'Senha'));
?>
<?php echo $this->Form->end(__('Logar')); ?>
	</fieldset>
</div>