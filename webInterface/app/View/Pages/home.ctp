<div class="tagids index"><p class="welcome">Bem Vindo <span class="username"><?php echo $current_user['username']; ?></span>, hoje é <?php echo date('d/m/Y'); ?>.</p></div>

<div class="actions">
	<h3><?php echo __('Actions'); ?></h3>
	<ul>
		<li><?php echo $this->Html->link(__('Log de acessos'), array('controller' => 'accesslogs' ,'action' => 'index')); ?></li>
		<li><?php echo $this->Html->link(__('Listar Usuários'), array('controller' => 'users' ,'action' => 'index')); ?></li>
		<li><?php echo $this->Html->link(__('Adicionar Usuário'), array('controller' => 'users' ,'action' => 'add')); ?></li>
		<li><?php echo $this->Html->link(__('Listar Tags'), array('controller' => 'tagids', 'action' => 'index')); ?> </li>
		<li><?php echo $this->Html->link(__('Adicionar Tag'), array('controller' => 'tagids' ,'action' => 'add')); ?></li>
		<li><?php echo $this->Html->link(__('Listar Usuários/Tags'), array('controller' => 'tagidsUsers' ,'action' => 'index')); ?></li>
		<li><?php echo $this->Html->link(__('Associar Usuários/Tag'), array('controller' => 'tagidsUsers' ,'action' => 'add')); ?></li>

	</ul>
</div>