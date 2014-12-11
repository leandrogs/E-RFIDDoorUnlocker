<div class="accesslogs index">
	<h2><?php echo __('Log de acessos'); ?></h2>
	<table cellpadding="0" cellspacing="0">
	<thead>
	<tr>
			<th><?php echo $this->Paginator->sort('tagid_id', $title = 'Tag ID'); ?></th>
			<th><?php echo $this->Paginator->sort('user_id', $title = 'Usuário'); ?></th>
			<th><?php echo $this->Paginator->sort('created', $title = 'Data do acesso'); ?></th>
	</tr>
	</thead>
	<tbody>
	<?php foreach ($accesslogs as $accesslog): ?>
	<tr>
		<td>
			<?php echo $this->Html->link($accesslog['Tagid']['tagid'], array('controller' => 'tagids', 'action' => 'view', $accesslog['Tagid']['id'])); ?>
		</td>
		<td>
			<?php echo $this->Html->link($accesslog['User']['username'], array('controller' => 'users', 'action' => 'view', $accesslog['User']['id'])); ?>
		</td>
		<td><?php echo h($accesslog['Accesslog']['created']); ?>&nbsp;</td>
	</tr>
<?php endforeach; ?>
	</tbody>
	</table>
	<p>
	<?php
	echo $this->Paginator->counter(array(
	'format' => __('Page {:page} of {:pages}, showing {:current} records out of {:count} total, starting on record {:start}, ending on {:end}')
	));
	?>	</p>
	<div class="paging">
	<?php
		echo $this->Paginator->prev('< ' . __('previous'), array(), null, array('class' => 'prev disabled'));
		echo $this->Paginator->numbers(array('separator' => ''));
		echo $this->Paginator->next(__('next') . ' >', array(), null, array('class' => 'next disabled'));
	?>
	</div>
</div>
<div class="actions">
	<h3><?php echo __('Actions'); ?></h3>
	<ul>
		<li><?php echo $this->Html->link(__('Menu Principal'), array('controller' => 'pages' ,'action' => 'index')); ?></li>
		<li><?php echo $this->Html->link(__('Listar Usuários'), array('controller' => 'users', 'action' => 'index')); ?> </li>
		<li><?php echo $this->Html->link(__('Listar Tags'), array('controller' => 'tagids', 'action' => 'index')); ?> </li>
	</ul>
</div>
